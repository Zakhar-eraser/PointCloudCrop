#pragma once

#include <UnigineWidgets.h>
#include <UnigineGui.h>

using namespace Unigine;

class MainGUI
{
public:
  MainGUI() = default;
  MainGUI(GuiPtr gui);
  ~MainGUI() = default;

  void CreateMessageWidget(const char* message);
  void SetOpenCallback(CallbackBase2<const char*, float>* callback);
private:
  void MenuBoxCallback(WidgetMenuBoxPtr menuBox);

  CallbackBase2<const char*, float>* openFileCallback;
  void CreateFileDialog();

  void ShowDialog(WidgetPtr dialog);
  void RemoveWidget(WidgetPtr widget);
  void FileDialogOkCbk(WidgetDialogFilePtr dialog);

  char fileDialogPath[100];

  WidgetMenuBarPtr menuBar;
  WidgetDialogFilePtr openDialogFile;
  WidgetDialogFilePtr saveDialogFile;

  GuiPtr gui;
};

