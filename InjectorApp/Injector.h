#pragma once
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <iostream>

namespace InjectorApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace std;


	/// <summary>
	/// Summary for Injector
	/// </summary>
	public ref class Injector : public System::Windows::Forms::Form
	{
	public:
		Injector(void)
		{
			InitializeComponent();
			CheckUserLevel();
			GetProcessList();
			
			//
			//TODO: Add the constructor code here
			//
		}
		void GetProcessList();
		void addMessage(String^ msg);
		void startInjection(char* _dll, int _procID);
		void CheckUserLevel();
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Injector()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::Button^  button2;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Injector::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(108, 51);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"label1";
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.BackgroundImage")));
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(575, 99);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(20, 154);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(232, 55);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Browse for DLLs";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Injector::browse_click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(15, 126);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(181, 25);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Selected DLL file:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::Red;
			this->label3->Location = System::Drawing::Point(17, 212);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(141, 16);
			this->label3->TabIndex = 4;
			this->label3->Text = L"<nothing selected yet>";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(12, 250);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(184, 25);
			this->label4->TabIndex = 5;
			this->label4->Text = L"Selected process:";
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(20, 278);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(232, 21);
			this->comboBox1->TabIndex = 6;
			this->comboBox1->DropDownStyle = ComboBoxStyle::DropDownList;
			this->comboBox1->Text = L"<select process>";
			// 
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->richTextBox1->ForeColor = System::Drawing::Color::Red;
			this->richTextBox1->Location = System::Drawing::Point(281, 126);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->Size = System::Drawing::Size(306, 298);
			this->richTextBox1->TabIndex = 8;
			this->richTextBox1->Text = L"";
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::SeaShell;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->ForeColor = System::Drawing::Color::Red;
			this->button2->Location = System::Drawing::Point(20, 317);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(232, 107);
			this->button2->TabIndex = 9;
			this->button2->Text = L"Inject";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &Injector::inject_click);
			// 
			// Injector
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->ClientSize = System::Drawing::Size(610, 453);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label1);
			this->Name = L"Injector";
			this->Text = L"Injector";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion



private: System::Void browse_click(System::Object^  sender, System::EventArgs^  e) {
	OpenFileDialog^ fd = gcnew OpenFileDialog();
	fd->Filter = "DLL files (.dll)|*.dll";
	
	if (fd->ShowDialog() == System::Windows::Forms::DialogResult::OK){
		label3->Text = fd->FileName;
	}

}
	
	

private: System::Void inject_click(System::Object^  sender, System::EventArgs^  e) {
	char* dll;
	int pid;
	
	if (label3->Text != "<nothing selected yet>"){
		IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(label3->Text);
		dll = static_cast<char*>(ptrToNativeString.ToPointer());
		if (comboBox1->Text != ""){
			addMessage("Starting injection...");
			array<String^>^ splitted = comboBox1->Text->Split(' ');
			pid = Convert::ToInt32(splitted[splitted->Length - 1]);
			startInjection(dll, pid);
		}
	}else{

	}
}


};
}
