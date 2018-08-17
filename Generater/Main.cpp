//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	ToolVersion->Text = "1.0";
	ToolValidityDays->Text = "365";
	ToolUseCount->Text = "100";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::LocalClick(TObject *Sender)
{
	generate_LocalLicence();
	ShowMessage("Generate Success!!");
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::ServerClick(TObject *Sender)
{
	generate_ServerLicence();
	ShowMessage("Generate Success!!");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AllClick(TObject *Sender)
{
	generate_LocalLicence();
	generate_ServerLicence();
	ShowMessage("Generate Success!!");
}
//---------------------------------------------------------------------------

