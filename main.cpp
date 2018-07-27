
#include "CYdLidar.h"
#include <iostream>
#include <signal.h>
#include <memory>
#include <unistd.h>
#include <thread>
#include <vector>
#include <map>
#include <fstream>
using namespace std;
using namespace ydlidar;

#include "third/pub.h"

CYdLidar laser;
static bool running = false;

const std::string port = "/dev/ydlidar";
const int baud = 115200;
const int intensities = 0;

static void
Stop(int signo)
{

    printf("Received exit signal\n");
    running = true;

}

void
GetYdlidarData()
{
    laser.setSerialPort(port);
    laser.setSerialBaudrate(baud);
    laser.setIntensities(intensities);

    laser.initialize();
    while (!running)
    {
        bool hardError;
        LaserScan scan;

        if (laser.doProcessSimple(scan, hardError))
        {
            //fprintf(stderr, "Scan received: %u ranges\n", (unsigned int) scan.ranges.size());
            //fprintf(stderr, "Scan received: %u intensities\n", (unsigned int) scan.intensities.size());
            /*
            for(auto v:scan.ranges)
            {
                cout<<v<<std::endl;
            }
             */
            std::cout << "Scan received: " << (unsigned int) scan.ranges.size() << " ranges" << std::endl;
            std::cout << "Scan received: " << (unsigned int) scan.intensities.size() << " intensities" << std::endl;
            /*
            for(auto v:scan.intensities)
            {
                cout<<v<<std::endl;
            }
             */
        }
        usleep(50 * 1000);

    }
    laser.turnOff();
    laser.disconnecting();

    return;
}


int
main(int argc, char *argv[])
{
//    std::thread dealydliar(GetYdlidarData);
//    dealydliar.join();
/*
    std::map<int, int> trymap;
    int &trymap_value = trymap[1];
    trymap_value = 100;
    std::cout<<trymap[1]<<std::endl;
    std::cout<<trymap.size()<<std::endl;

    for(int i = 0; i < 10; i++)
    {
        std::string tmpstr;
        std::stringstream tmpstream;
        tmpstream<<i;
        tmpstr = tmpstream.str();
        tmpstr += ".png";
        std::cout<<tmpstr.data()<<std::endl;
    }
*/

    while(true)
    {
        int iport = 11999;
        std::cout<<"recv is beigin!"<<std::endl;
        if(1 == recv_work(iport))
        {
            std::cout<<"recv success!"<<std::endl;
        }
        usleep(3000);
    }

    return 0;
}