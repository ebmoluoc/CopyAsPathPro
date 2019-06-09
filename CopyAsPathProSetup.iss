[Setup]
AppId={{3BC6CB12-5A75-4F54-A8CB-E012F73ECC5E}
SetupMutex=Global\3BC6CB12-5A75-4F54-A8CB-E012F73ECC5E
AppCopyright=Copyright (c) 2019 Philippe Coulombe
AppPublisher=Philippe Coulombe
AppVersion=1.1.0.0
VersionInfoVersion=1.1.0.0
AppVerName=CopyAsPath Pro 1.1
AppName=CopyAsPath Pro
DefaultDirName={commonpf}\CopyAsPath Pro
OutputBaseFilename=CopyAsPathProSetup
OutputDir=.
LicenseFile=LICENSE
DisableProgramGroupPage=yes
DisableDirPage=yes
SolidCompression=yes
ArchitecturesAllowed=x64
ArchitecturesInstallIn64BitMode=x64
MinVersion=6.1.7601
WizardSizePercent=120,100

[Files]
Source: "LICENSE"; DestDir: {app}; Flags: restartreplace uninsrestartdelete ignoreversion
Source: "x64\Release\CopyAsPathPro.dll"; DestDir: {app}; Flags: restartreplace uninsrestartdelete ignoreversion regserver

[Code]
procedure InitializeWizard();
begin
    WizardForm.LicenseMemo.Font.Name := 'Consolas';
end;
