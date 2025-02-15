//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdIcmpClient.hpp>
#include <IdRawBase.hpp>
#include <IdRawClient.hpp>
#include <Vcl.ExtCtrls.hpp>

#include <vector>
using namespace std;
//---------------------------------------------------------------------------
struct HostEntry
{
	public:
	UnicodeString Host;
	int AlarmCount;
};
//---------------------------------------------------------------------------
struct AlarmEntry
{
	public:
	UnicodeString Time;
	UnicodeString Host;
};
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *LE1;
	TButton *B1;
	TMemo *Memo1;
	TIdIcmpClient *Icmp1;
	TTimer *T1;
	TPanel *P1;
	TMemo *Memo2;
	void __fastcall B1Click(TObject *Sender);
	void __fastcall Icmp1Reply(TComponent *ASender, TReplyStatus * const AReplyStatus);
	void __fastcall T1Timer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);


private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);


	vector <HostEntry> ar;
    vector <AlarmEntry> Alarms;
	int nHostNumber;
	int nOneCircleAlarms;


    bool CheckGateway(UnicodeString sGate);
	bool Preparation();


	UnicodeString GetCurrDir();
	UnicodeString GetDefaultGateway();
	void SaveLogs();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
