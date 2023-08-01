#include "MainGUI.h"

MainGUI::MainGUI(GuiPtr gui)
{
  this->gui = gui;
  openFileCallback = nullptr;
  fileDialogPath[0] = 0;

  WidgetVBoxPtr container = WidgetVBox::create(gui, 0, 0);
  container->setBackground(1);
  menuBar = WidgetMenuBar::create(container->getGui(), 5, 5);
  menuBar->setFontSize(25);
  WidgetMenuBoxPtr fileMenuBox = WidgetMenuBox::create(menuBar->getGui(), 4, 4);
  fileMenuBox->addCallback(Gui::CLICKED, MakeCallback(this, &MainGUI::MenuBoxCallback, fileMenuBox));

  menuBar->addItem("File");
  fileMenuBox->setFontSize(20);
  fileMenuBox->addItem("Open");
  menuBar->setItemMenu(0, fileMenuBox);

  gui->addChild(container, Gui::ALIGN_FIXED);
  container->addChild(menuBar, Gui::ALIGN_LEFT);
}

void MainGUI::MenuBoxCallback(WidgetMenuBoxPtr menuBox)
{
  switch (menuBox->getCurrentItem())
  {
  case 0:
    CreateFileDialog();
  default:
    break;
  }
}

void MainGUI::CreateMessageWidget(const char* message)
{
  WidgetDialogMessagePtr messageDialog = WidgetDialogMessage::create(gui, message);
  ShowDialog(messageDialog);
}

void MainGUI::CreateFileDialog()
{
  WidgetDialogFilePtr fileDialog = WidgetDialogFile::create(gui, "Opening .pcd file");
  if (fileDialogPath[0] == 0)
  {
    char* homePath = std::getenv("HOMEPATH");
    char* homeDrive = std::getenv("HOMEDRIVE");
    std::strcpy(fileDialogPath, homeDrive);
    std::strcat(fileDialogPath, homePath);
    std::strcat(fileDialogPath, "\\");
  }
  fileDialog->setPath(fileDialogPath);
  fileDialog->setFilter(".pcd");
  if (openFileCallback != nullptr)
    fileDialog->getOkButton()->addCallback(Gui::CLICKED, MakeCallback(this, &MainGUI::FileDialogOkCbk, fileDialog));
  fileDialog->getOkButton()->addCallback(Gui::CLICKED, MakeCallback(this, &MainGUI::FileDialogOkCbk, fileDialog));
  fileDialog->getCancelButton()->addCallback(Gui::CLICKED, MakeCallback(this, &MainGUI::RemoveWidget, static_ptr_cast<Widget>(fileDialog)));
  ShowDialog(fileDialog);
}

void MainGUI::ShowDialog(WidgetPtr dialog)
{
  gui->addChild(dialog, Gui::ALIGN_CENTER | Gui::ALIGN_OVERLAP);
  dialog->setPermanentFocus();
}

void MainGUI::SetOpenCallback(CallbackBase2<const char*, float>*callback)
{
  openFileCallback = callback;
}

void MainGUI::RemoveWidget(WidgetPtr widget)
{
  widget.deleteLater();
}

void MainGUI::FileDialogOkCbk(WidgetDialogFilePtr dialog)
{
  std::strcpy(fileDialogPath, dialog->getPath());
  RemoveWidget(static_ptr_cast<Widget>(dialog));
  openFileCallback->run(dialog->getFile(), 1);
}
