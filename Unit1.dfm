object Form1: TForm1
  Left = 686
  Top = 386
  Caption = 'EcoCheck'
  ClientHeight = 169
  ClientWidth = 408
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Times New Roman'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 15
  object P1: TPanel
    Left = 8
    Top = 8
    Width = 393
    Height = 153
    TabOrder = 0
    object Memo1: TMemo
      Left = 8
      Top = 76
      Width = 377
      Height = 65
      TabStop = False
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -8
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
      WordWrap = False
    end
    object LE1: TLabeledEdit
      Left = 8
      Top = 27
      Width = 185
      Height = 23
      EditLabel.Width = 33
      EditLabel.Height = 15
      EditLabel.Caption = #1064#1083#1102#1079
      TabOrder = 1
    end
    object B1: TButton
      Left = 208
      Top = 17
      Width = 177
      Height = 33
      Caption = #1053#1072#1095#1072#1090#1100' '#1087#1088#1086#1074#1077#1088#1082#1091
      TabOrder = 2
      OnClick = B1Click
    end
    object Memo2: TMemo
      Left = 8
      Top = 56
      Width = 377
      Height = 20
      Alignment = taCenter
      BevelInner = bvNone
      BevelOuter = bvNone
      BorderStyle = bsNone
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentColor = True
      ParentFont = False
      TabOrder = 3
    end
  end
  object Icmp1: TIdIcmpClient
    ReceiveTimeout = 2000
    Protocol = 1
    ProtocolIPv6 = 58
    IPVersion = Id_IPv4
    OnReply = Icmp1Reply
    Left = 96
    Top = 8
  end
  object T1: TTimer
    Enabled = False
    OnTimer = T1Timer
    Left = 136
    Top = 8
  end
end