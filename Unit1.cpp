//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	HostEntry eHost = {"ya.ru", 0};
	ar.push_back(eHost);
	eHost.Host = "8.8.8.8";
	ar.push_back(eHost);
	eHost.Host = "193.105.59.6";
	ar.push_back(eHost);
	eHost.Host = "193.105.59.2";
	ar.push_back(eHost);

	nHostNumber = 0;
	nOneCircleAlarms = 0;
}
//---------------------------------------------------------------------------
bool TForm1::CheckGateway(UnicodeString sGate)
{
	if(sGate=="")
    	return true;

	int nPos = sGate.Pos(".");
	if(!nPos)
		return false;

	nPos = sGate.Pos(" ");
	while(nPos)
	{
		sGate.Delete(nPos, 1);
        nPos = sGate.Pos(" ");
	}

	Icmp1->Host = sGate;
	try
	{
		Icmp1->Ping();
	}
	catch(...)
	{
    	return false;
	}

return true;
}
//---------------------------------------------------------------------------
bool TForm1::Preparation()
{
	Memo2->Lines->Strings[0] = "����������...";
	B1->Enabled = false;
	P1->Enabled = false;

	if(!CheckGateway(LE1->Text))
	{
		Memo2->Lines->Strings[0] = "������������ ���������� � ���� ����!";
		B1->Enabled = true;
		P1->Enabled = true;
		return false;
	}
return true;
}
//---------------------------------------------------------------------------
UnicodeString TForm1::GetCurrDir()
{
  	TCHAR thBuffer[MAX_PATH];
    GetModuleFileName(NULL, thBuffer, MAX_PATH);
	UnicodeString str = UnicodeString(thBuffer);
	str = str.SubString(0, str.Length()-12); // EcoCheck.exe
return str;
}
//---------------------------------------------------------------------------
UnicodeString TForm1::GetDefaultGateway()
{
	UnicodeString sGate, sFileName = GetCurrDir() + "CheckResult.txt";
	UnicodeString str = "ipconfig > " + sFileName;
	system(AnsiString(str).c_str());
	Sleep(1000);

    Memo1->Lines->Clear();
	Memo1->Lines->LoadFromFile(sFileName);
	int i = Memo1->Lines->Count;
	int nPos=0;
	while(nPos<=0 && i>0)
	{
		str = Memo1->Lines->Strings[--i];
		nPos = str.Pos("192.168.");
		if(nPos>0)
			sGate = str.SubString(nPos, str.Length()-nPos+1);
	}
    Memo1->Lines->Clear();
return sGate;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::B1Click(TObject *Sender)
{
	Memo2->Lines->Clear();
	if(!Preparation())
		return;

	HostEntry eHost = {"", 0};
	UnicodeString sGate;
	if(LE1->Text!="")
	{
		eHost.Host = LE1->Text;
		ar.push_back(eHost);
	}
	sGate = GetDefaultGateway();
	if(sGate!="" && sGate!=LE1->Text)
	{
		eHost.Host = sGate;
		ar.push_back(eHost);
	}
	T1->Enabled = true;

    Memo2->Lines->Clear();
	Memo2->Lines->Strings[0] = "...���� ��������...";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::T1Timer(TObject *Sender)
{
	nOneCircleAlarms = 0;
	nHostNumber = ar.size();
	try
	{
		for(int i=ar.size()-1; i>=0; i--)
		{
			Icmp1->Host = ar[i].Host;
			try
			{
				Icmp1->Ping();
			}
			catch(...)
			{
				Memo1->Lines->Add("���� " + ar[i].Host + " ���� ��������");
				nHostNumber--;
            }
		}
		Memo1->Lines->Add("");
	}
	catch(...)
	{
		Memo1->Lines->Add("����� ����");
		T1->Enabled = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Icmp1Reply(TComponent *ASender, TReplyStatus * const AReplyStatus)
{
	if(!T1->Enabled)
		return;

	nHostNumber--;
	int nAlarmCount;
	AlarmEntry eAlarm;
	UnicodeString str = "[" + Now() + "] ����� �� " + ar[nHostNumber].Host + " (" + AReplyStatus->FromIpAddress + ")";
	if(AReplyStatus->BytesReceived == 0)
	{
		nOneCircleAlarms++;
		str+= ": ---";
		nAlarmCount = ar[nHostNumber].AlarmCount+1;
		if(nAlarmCount == 2 || nOneCircleAlarms==2)
		{
			eAlarm.Time = Now();
			eAlarm.Host = ar[nHostNumber].Host;
			Alarms.push_back(eAlarm);
		}
		ar[nHostNumber].AlarmCount = nAlarmCount;

		if(nAlarmCount>20)
		{
			Memo1->Lines->Add("Host " + ar[nHostNumber].Host + " was deleted");
			HostEntry *eHost = &ar[nHostNumber];
			ar.erase(eHost);
		}
	}
	else
	{
		str += ": �����";
		unsigned int t = AReplyStatus->MsRoundTripTime;
		if(t<1)
			str += "<1";
		else
			str += "=" + UnicodeString(t);

        ar[nHostNumber].AlarmCount = 0;
	}
	Memo1->Lines->Add(str);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	UnicodeString sFileName = GetCurrDir() + "CheckResult.txt";
	Memo1->Lines->Add("Alarms to check:");
	for(int n=0; n<Alarms.size(); n++)
		Memo1->Lines->Add("[" + Alarms[n].Time + "] Host: " + Alarms[n].Host);

	Memo1->Lines->SaveToFile(sFileName);
}
//---------------------------------------------------------------------------
