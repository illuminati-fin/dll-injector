#include "Injector.h"
#include "stdafx.h"
#include <stdio.h>

using namespace System;
using namespace System::Security::Principal;
using namespace System::Windows::Forms;

[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	InjectorApp::Injector injector;
	Application::Run(%injector);


}


//this will get the list of all processes
void InjectorApp::Injector::GetProcessList(void){
	HANDLE snapshot = INVALID_HANDLE_VALUE;
	PROCESSENTRY32 procInfo;
	procInfo.dwSize = sizeof(procInfo);
	String^ processName;
	String^ processID;


	try {
		comboBox1->Items->Clear();
		snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		
		if (snapshot == INVALID_HANDLE_VALUE){
			throw gcnew Exception("Could not get snapshot!");
		}

		if (!Process32First(snapshot, &procInfo)){
			CloseHandle(snapshot);
			throw gcnew Exception("Could not get first process!");
		}

		do
		{
			processName = gcnew String(procInfo.szExeFile);
			processID = System::Convert::ToString(gcnew Int32(procInfo.th32ProcessID));
			comboBox1->Items->Add(processName + "    PID: " + processID);

		} while (Process32Next(snapshot, &procInfo));
		CloseHandle(snapshot);
		addMessage("System processes succesfully loaded!");
	}
	catch (Exception^ e){

	}
}

//add message to the logview
void InjectorApp::Injector::addMessage(String^ msg){
	String^ format = "hh:mm:ss";
	DateTime time = DateTime::Now;
	String^ timestr = time.ToString(format);
	richTextBox1->AppendText(timestr + " --- " + msg + "\n");
	richTextBox1->ScrollToCaret();
}

//check if the injector is being run as admin or if not 
void InjectorApp::Injector::CheckUserLevel(){
	WindowsIdentity^ ident = WindowsIdentity::GetCurrent();
	WindowsPrincipal^ princip = gcnew WindowsPrincipal(ident);
	bool isAdmin = princip->IsInRole(WindowsBuiltInRole::Administrator);
	if (!isAdmin){
		MessageBox::Show("You are currently NOT running the DLL injector as administrator.\nWhile in many cases this is perfectly ok, remember that some actions of the DLL you are about to inject, may require administrator level privileges.\nHowever...if the target process in being run as non-admin, running the injector as admin will not be enough.\n\nSo to put it short:\nFor administrator level stuff remember to run both: the target process and this injector as administrator.\n\nHappy hacking! :)", "DLL Injector");
	}
}

//the actual injection
void InjectorApp::Injector::startInjection(char* _dll, int _procID){
	char* buffer = _dll; //"C:\\drivers\\dllinject.dll";
	int procID = _procID; //60740;

	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
	if (process == NULL){
		addMessage("ERROR! Process not found with given PID: " + procID.ToString());
	}else{
		addMessage("Process found.");
	}

	LPVOID addr = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");
	if (addr == NULL){
		addMessage("ERROR! LoadLibraryA not found from the kernel32.dll library.");
	}else{
		addMessage("LoadLibraryA found from Kernel32.dll.");
	}

	LPVOID arg = (LPVOID)VirtualAllocEx(process, NULL, strlen(buffer), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (arg == NULL){
		addMessage("ERROR! Memory could not be allocated inside the chosen process!");
	}else{
		addMessage("Virtual memory allocation completed.");
	}

	int n = WriteProcessMemory(process, arg, buffer, strlen(buffer), NULL);
	if (n == 0) {
		addMessage("ERROR! Could not write to the memory space of the selected process!");
	}else{
		addMessage("Writing to target process memory space...");
	}

	HANDLE threadID = CreateRemoteThread(process, NULL, 0, (LPTHREAD_START_ROUTINE)addr, arg, NULL, NULL);
	if (threadID == NULL) {
		addMessage("ERROR! Could not create remote thread!\n\n");
	}
	else{
		addMessage("SUCCESS! Remote thread successfully created!");
		addMessage("DLL Injection completed!\n\n");
	}

	CloseHandle(process);
}