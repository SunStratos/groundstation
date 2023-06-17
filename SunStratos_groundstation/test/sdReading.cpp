#include "dataLog.h"

void setup()
{
    Serial.begin(115200);
    while(!Serial);

    if (!sdSMT.begin(SMT_SD_CONFIG))
    {
        sdSMT.initErrorHalt(&Serial);
    }

    if (!fileSMT.open("sdDataLog0.csv", FILE_READ)) 
    {
        Serial.printf("%s open failed\n\n", fileName);
        while (true);
    }

    fileSMT.rewind();

    while (fileSMT.available()) 
    {
        int n = fileSMT.fgets(line, sizeof(line));
        if (n <= 0) 
        {
            Serial.println("fgets failed");
        }
        if (line[n-1] != '\n' && n == (sizeof(line) - 1)) 
        {
            Serial.println("line too long");
        }
        if (!parseLine(line)) 
        {
            Serial.println("parseLine failed");
        }
        Serial.println(line);
    }
    fileSMT.close();
    Serial.println("Done.");
}

void loop()
{

}