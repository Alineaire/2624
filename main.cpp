#include "ReaderScenario.h"
#include "TagsManager.h"
#include "LocalisationManager.h"
#include "ScenarioData.h"
#include "Time.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "window.h"

#include "led-matrix.h"

#include <getopt.h>
#include <iostream>
#include <signal.h>
#include <string>
#include <string.h>
#include <time.h>
#include <unistd.h>

using namespace std;
using namespace rgb_matrix;

ReaderScenario* ReaderScenario::m_instance = nullptr;
TagsManager* TagsManager::m_instance = nullptr;
LocalisationManager* LocalisationManager::m_instance = nullptr;
Time* Time::m_instance = nullptr;
InputManager* InputManager::m_instance = nullptr;
SoundManager* SoundManager::m_instance = nullptr;

#if 1
static int usage(const char *progname)
{
    fprintf(stderr, "usage: %s [options]\n", progname);
    fprintf(stderr, "Reads text from stdin and displays it. "
          "Empty string: clear screen\n");
    fprintf(stderr, "Options:\n");
    rgb_matrix::PrintMatrixFlags(stderr);
    fprintf(stderr,
            "\t-f <font-file>       : Use given font.\n"
            "\t-s <scenario>        : Use given scenario.\n"
            "\t-l <localisation>    : Use given localisation.\n"
            );
    return 1;
}

volatile bool interrupt_received = false;
static void InterruptHandler(int signo)
{
  interrupt_received = true;
}

int main(int argc, char *argv[])
{
    RGBMatrix::Options matrix_options;
    rgb_matrix::RuntimeOptions runtime_opt;
    if (!rgb_matrix::ParseOptionsFromFlags(&argc, &argv, &matrix_options, &runtime_opt))
        return usage(argv[0]);
    runtime_opt.drop_privileges = -1;

    const char* bdf_font_file = NULL;
    const char* scenario_file = NULL;
    const char* localisation_file = NULL;
    int opt;
    while ((opt = getopt(argc, argv, "f:s:l:")) != -1)
    {
        switch (opt)
        {
        case 'f': bdf_font_file = strdup(optarg); break;
        case 's': scenario_file = strdup(optarg); break;
        case 'l': localisation_file = strdup(optarg); break;
        default:
          return usage(argv[0]);
        }
    }

    // Font
    if (bdf_font_file == NULL)
    {
        fprintf(stderr, "Need to specify BDF font-file with -f\n");
        return usage(argv[0]);
    }
    rgb_matrix::Font font;
    if (!font.LoadFont(bdf_font_file))
    {
        fprintf(stderr, "Couldn't load font '%s'\n", bdf_font_file);
        return 1;
    }

    // Initialize matrix
    RGBMatrix* matrix = rgb_matrix::CreateMatrixFromOptions(matrix_options, runtime_opt);
    if (matrix == NULL)
        return 1;

    matrix->SetBrightness(70);

    FrameCanvas* offscreen = matrix->CreateFrameCanvas();

    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    try
    {
        window* windows = new window();
        SoundManager::Instance()->init();
        Time::Instance()->init();

        string pathLoc(localisation_file);
        LocalisationManager::Instance()->loadTSV(pathLoc);
        string pathScenario(scenario_file);
        ScenarioData scenario(pathScenario);

        ReaderScenario::Instance()->start(matrix, offscreen, &font, &scenario);

        while (!interrupt_received)
        {
            InputManager::Instance()->update();
            ReaderScenario::Instance()->update();
            windows->draw();

            // Atomic swap with double buffer
            //usleep(500);
            offscreen = matrix->SwapOnVSync(offscreen);
            offscreen->Clear();

            Time::Instance()->update();
        }
        delete windows;
    }
    catch ( const InitError & err )
    {
        cerr << "Error while initializing SDL: " << err.what() << endl;
    }

    delete SoundManager::Instance();
    delete InputManager::Instance();
    delete Time::Instance();
    delete LocalisationManager::Instance();
    delete TagsManager::Instance();
    delete ReaderScenario::Instance();

    // Finished. Shut down the RGB matrix.
    matrix->Clear();
    delete matrix;

    return 0;
}
#endif
