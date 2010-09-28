; -- Example1.iss --
; Demonstrates copying 3 files and creating an icon.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!

[Setup]
AppName=dEspresso
AppVerName=dEspresso version 1.0
DefaultDirName={pf}\dEspresso
DefaultGroupName=dEspresso
UninstallDisplayIcon={app}\dEspressoUninstall.exe
Compression=lzma
SolidCompression=yes
OutputDir=userdocs:Inno Setup Examples Output

[Files]
Source: dEspressoLauncher.exe; DestDir: {app}
Source: dEspressoUpdate.dll; DestDir: {app}
Source: mfc80u.dll; DestDir: {app}

[Icons]
Name: {group}\dEspresso; Filename: {app}\dEspressoLauncher.exe
