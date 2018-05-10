#include "brewtools.h"
#include <cmath> // cos, sin
#include <string.h>

int main()
{
  BrewTools::Engine *engine = BrewTools::Engine::Get();
  // First create trace
  BrewTools::Trace *trace = engine->GetSystem<BrewTools::Trace>();
  // Then create gfx so we can create consoles
  BrewTools::Graphics *gfx = engine->GetSystem<BrewTools::Graphics>();
  // Then link the trace to a console
  BrewTools::Console *bconsole =
    new BrewTools::Console("Bottom Screen", BrewTools::Window::Screen::BOTTOM);
  trace->OpenFile("BTTrace.log");
  trace->SelectConsole(bconsole);
  // Setting max print level to lower than 5 means BT messages aren't printed
  trace->SetMaxPrintLevel(4);

  // Initialize all other systems
  engine->InitializeAll();
  BrewTools::Time *time = engine->GetSystem<BrewTools::Time>();
  BrewTools::Graphics::Triangle tri(
    -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f
  );
  (*trace)[0] << "Hello World!";

  gfx->GetCurrentWindow()->SetBG(0x224444FF);
  #ifdef _WIN32
  (*trace)[1] << "I'm running on Windows";
  #elif _3DS
  (*trace)[1] << "I'm running on 3DS";
  #elif _WIIU
  (*trace)[1] << "I'm running on Wii U";
  #endif

  // Main loop
  (*trace)[0] << "Starting loop...";
  while (engine->Update())
  {
    long long unsigned t = time->Current();
    tri.position.x = cos(t * 0.001);
    tri.position.y = sin(t * 0.001);

    // Render the scene
    (*trace)[3] << "Drawing triangle " << (t - time->Start()) * 0.001;
    tri.Draw();

    // After frame
    //(*trace)[4] << "Sleeping for 1 second...";
    //time->Sleep(1000);
    (*trace)[100] << "";
  }
  SAFE_DELETE(bconsole);
  engine->Shutdown();

  return 0;
}
