#include "BitWave.h"
#include "BitFile.h"
#include "BitCreator.h"
#include "BitService.h"
#include "bencode/MetainfoFile.h"
#include "../base/StringConv.h"
#include <iostream>

void ProcessException(const bitwave::core::bentypes::BenTypeException& bte)
{
    std::cout << "torrent file is invalidate!" << std::endl;
}

void ProcessException(const bitwave::core::bentypes::MetainfoFileExeception& mfe)
{
    std::cout << mfe.what() << std::endl;
}

void ProcessException(const bitwave::core::BitFile::CreateFileError& cfe)
{
    switch (cfe.GetErrorCode())
    {
    case bitwave::core::BitFile::CreateFileError::PATH_ERROR:
        std::cout << "download_path is invalidate, can not create download files!" << std::endl;
        break;
    case bitwave::core::BitFile::CreateFileError::SPACE_NOT_ENOUGH:
        std::cout << "disk space not enough, can not create download files!" << std::endl;
        break;
    }
}

int main(int argc, const char **argv)
{
    if (argc != 3)
    {
        std::cout << "error command, please input command like this:" << std::endl;
        std::cout << "\tBitTorrent torrent download_path" << std::endl;
        return 0;
    }

    try
    {
        std::string torrent = ANSIToUTF8(argv[1]);
        std::string download_path = ANSIToUTF8(argv[2]);

        bitwave::core::BitWave wave;
        bitwave::core::BitNetWaveObject net_wave_object;
        bitwave::core::BitCoreControlObject core_control_object;
        bitwave::core::BitConsoleShowerObject console_shower_object;

        bitwave::core::BitService::new_task_creator->CreateTask(torrent, download_path);

        wave.AddWaveObject(&net_wave_object);
        wave.AddWaveObject(&core_control_object);
        wave.AddWaveObject(&console_shower_object);
        wave.Wave();
    }
    catch (const bitwave::core::bentypes::BenTypeException& bte)
    {
        ProcessException(bte);
    }
    catch (const bitwave::core::bentypes::MetainfoFileExeception& mfe)
    {
        ProcessException(mfe);
    }
    catch (const bitwave::core::BitFile::CreateFileError& cfe)
    {
        ProcessException(cfe);
    }
    catch (...)
    {
        std::cout << "sorry, program occur a problem, need to exit!" << std::endl;
    }

    return 0;
}
