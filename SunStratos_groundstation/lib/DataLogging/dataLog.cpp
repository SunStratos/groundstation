#include "dataLog.h"

SdFs sdTNS;
FsFile fileTNS;

SdFs sdSMT;
FsFile fileSMT;

RingBuf<FsFile, RING_BUF_CAPACITY> rbTNS;
RingBuf<FsFile, RING_BUF_CAPACITY> rbSMT;

DataLogStruct data;

char line[70];

void teensySDSetup(unsigned long long timeStamp, bool removeFile)
{
    char fileName[20];
    sprintf(fileName, "tnsDataLog%llu.csv", timeStamp);

    if (!sdTNS.begin(TEENSY_SD_CONFIG))
    {
        sdTNS.initErrorHalt(&Serial);
    }

    if (sdTNS.exists(fileName) && removeFile)
    {
        sdTNS.remove(fileName);
        Serial.println("File already exists - deleting.");
    }

    // Open or create file - truncate existing file.
    if (!fileTNS.open(fileName, O_RDWR | O_CREAT | O_TRUNC)) 
    {
        Serial.printf("%s open failed\n\n", fileName);
        while (true);
    }

    // File must be pre-allocated to avoid huge
    // delays searching for free clusters.
    if (!fileTNS.preAllocate(LOG_FILE_SIZE)) 
    {
        Serial.println("preAllocate failed\n");
        fileTNS.close();
        while (true);
    }

    // initialize the RingBuf.
    rbTNS.begin(&fileTNS);
    Serial.printf("Teensy SD Card set up complete.\n");
}

void smtSDSetup(unsigned long long timeStamp, bool removeFile)
{
    char fileName[20];
    sprintf(fileName, "sdDataLog%llu.csv", timeStamp);

    if (!sdSMT.begin(SMT_SD_CONFIG))
    {
        sdSMT.initErrorHalt(&Serial);
    }

    if (sdSMT.exists(fileName) && removeFile)
    {
        sdSMT.remove(fileName);
        Serial.println("File already exists - deleting.");
    }

    // Open or create file - truncate existing file.
    if (!fileSMT.open(fileName, O_RDWR | O_CREAT | O_TRUNC)) 
    {
        Serial.printf("%s open failed\n\n", fileName);
        while (true);
    }

    // File must be pre-allocated to avoid huge
    // delays searching for free clusters.
    if (!fileSMT.preAllocate(LOG_FILE_SIZE)) {
        Serial.println("preAllocate failed\n");
        fileSMT.close();
        while (true);
    }

    // initialize the RingBuf.
    rbSMT.begin(&fileSMT);
    Serial.printf("SMT SD Card set up complete.\n");
}

void logData()
{
    // Max RingBuf used bytes. Useful to understand RingBuf overrun.
    size_t maxUsed = 0;

    size_t sizeCurr = rbSMT.bytesUsed();

    if ((sizeCurr + fileSMT.curPosition()) > (LOG_FILE_SIZE - 20))
    {
        Serial.println("File full - quitting.");
        fileSMT.close();
        while(true);
    }

    if (sizeCurr > maxUsed) 
    {
        maxUsed = sizeCurr;
    }

    if (sizeCurr >= 512 && !fileSMT.isBusy()) 
    {
        // Not busy only allows one sector before possible busy wait.
        // Write one sector from RingBuf to file.
        if (512 != rbSMT.writeOut(512)) 
        {
            Serial.println("writeOut failed");
            fileSMT.close();
            while(true);
        }
    }

    rbSMT.printf("%llu,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
        data.timeStamp,
        data.temp, data.accX, data.accY, data.accZ,
        data.gyrX, data.gyrY, data.gyrZ,
        data.gpsLat, data.gpsLon, data.gpsAlt, data.gpsSat,
        data.adxlX, data.adxlY, data.adxlZ,
        data.magX, data.magY, data.magZ
    );
    rbSMT.println();

    if (rbSMT.getWriteError()) 
    {
        // Error caused by too few free bytes in RingBuf.
        Serial.println("WriteError");
        fileSMT.close();
        while(1);
    }

    rbSMT.sync();
    fileSMT.truncate();

    // Serial.print("fileSize: ");
    // Serial.println((uint32_t)sdFile.fileSize());
    // Serial.print("maxBytesUsed: ");
    // Serial.println(maxUsed);
    // Serial.print("minSpareMicros: ");
    // Serial.println(minSpareMicros);
}

void transferData()
{
    teensySDSetup(micros(), true);

    while (fileSMT.available()) 
    {
        int n = fileSMT.fgets(line, sizeof(line));
        if (n <= 0) 
        {
            Serial.println("fgets failed");
            fileSMT.close();
            fileTNS.close();
        }
        if (line[n-1] != '\n' && n == (sizeof(line) - 1)) 
        {
            Serial.println("line too long");
            fileSMT.close();
            fileTNS.close();
        }
        if (!parseLine(line)) 
        {
            Serial.println("parseLine failed");
            fileSMT.close();
            fileTNS.close();
        }
    
        // Max RingBuf used bytes. Useful to understand RingBuf overrun.
        size_t maxUsed = 0;

        size_t sizeCurr = rbTNS.bytesUsed();

        if ((sizeCurr + fileTNS.curPosition()) > (LOG_FILE_SIZE - 20))
        {
            Serial.println("File full - quitting.");
            fileSMT.close();
            fileTNS.close();
            while(1);
        }

        if (sizeCurr > maxUsed) 
        {
            maxUsed = sizeCurr;
        }

        if (sizeCurr >= 512 && !fileTNS.isBusy()) 
        {
            // Not busy only allows one sector before possible busy wait.
            // Write one sector from RingBuf to file.

            if (512 != rbTNS.writeOut(512)) 
            {
                Serial.println("writeOut failed");
                fileSMT.close();
                fileTNS.close();
                while(1);
            }
        }

        rbTNS.printf("%s", line);
        rbTNS.println();

        if (rbTNS.getWriteError()) 
        {
            // Error caused by too few free bytes in RingBuf.
            Serial.println("WriteError");
            fileSMT.close();
            fileTNS.close();
            while(1);
        }

        rbTNS.sync();
        fileTNS.truncate();

        // Serial.print("fileSize: ");
        // Serial.println((uint32_t)sdFile.fileSize());
        // Serial.print("maxBytesUsed: ");
        // Serial.println(maxUsed);
        // Serial.print("minSpareMicros: ");
        // Serial.println(minSpareMicros);
        
        memset(line, 0, sizeof(line));
    }
    fileSMT.close();
    fileTNS.close();
}

char* skipSpace(char* str) 
{
    while (isspace(*str)) str++;
    return str;
}
//------------------------------------------------------------------------------
bool parseLine(char* str) 
{
    char* ptr;

    // Set strtok start of line.
    str = strtok(str, ",");
    if (!str) return false;

    // Subsequent calls to strtok expects a null pointer.
    str = strtok(nullptr, ",");
    if (!str) return false;

    // Convert string to long integer.
    int32_t i32 = strtol(str, &ptr, 0);
    if (str == ptr || *skipSpace(ptr)) return false;
    Serial.println(i32);

    str = strtok(nullptr, ",");
    if (!str) return false;

    // strtoul accepts a leading minus with unexpected results.
    if (*skipSpace(str) == '-') return false;

    // Convert string to unsigned long integer.
    uint32_t u32 = strtoul(str, &ptr, 0);
    if (str == ptr || *skipSpace(ptr)) return false;
    Serial.println(u32);

    str = strtok(nullptr, ",");
    if (!str) return false;

    // Convert string to double.
    double d = strtod(str, &ptr);
    if (str == ptr || *skipSpace(ptr)) return false;
    Serial.println(d);

    // Check for extra fields.
    return strtok(nullptr, ",") == nullptr;
}