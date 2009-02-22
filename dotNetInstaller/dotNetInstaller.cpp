// dotNetInstaller.cpp : definisce i comportamenti delle classi per l'applicazione.
//

#include "stdafx.h"
#include "ConfigFile.h"
#include "dotNetInstaller.h"
#include "dotNetInstallerDlg.h"
#include "InstallerCommandLineInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CdotNetInstallerApp

BEGIN_MESSAGE_MAP(CdotNetInstallerApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// costruzione di CdotNetInstallerApp

CdotNetInstallerApp::CdotNetInstallerApp()
{
	// Inserire l'inizializzazione significativa in InitInstance.
}


// L'unico e solo oggetto CdotNetInstallerApp

CdotNetInstallerApp theApp;


// Inizializzazione di CdotNetInstallerApp

BOOL CdotNetInstallerApp::InitInstance()
{
	// InitCommonControls() � necessario in Windows XP se nel manifesto
	// di un'applicazione � specificato l'utilizzo di ComCtl32.dll versione 6 o successiva per attivare
	// gli stili visuali. In caso contrario, non sar� possibile creare finestre.
	InitCommonControls();

	CWinApp::InitInstance();

	//AfxEnableControlContainer();

	CInstallerCommandLineInfo commandLineInfo;
	ParseCommandLine(commandLineInfo);

	TiXmlDocument m_Document;
	installerSetting m_Setting;

	try
	{
		//load xml file
		bool l_bLoadSuccess = LoadXmlSettings(m_Document);

		if (l_bLoadSuccess)
		{
			// Process xml file ("additional config" parameter needs defaulted to false)
			LoadConfigsNode(m_Document.FirstChildElement(), m_Setting, false);
		}
		else
		{
			DniSilentMessageBox(TEXT("Failed to read configuration file."), MB_OK|MB_ICONSTOP);
			PostQuitMessage(-1);
		}

		return l_bLoadSuccess;
	}
	catch(TCHAR * p_Message)
	{
		DniSilentMessageBox(p_Message, MB_OK|MB_ICONSTOP);
		return false;
	}
	catch(...)
	{
		DniSilentMessageBox(TEXT("Error loading configuration file"), MB_OK|MB_ICONSTOP);
		return false;
	}


	// Poich� la finestra di dialogo � stata chiusa, restituisce FALSE in modo che l'applicazione
	//  venga terminata, anzich� avviare la message pump dell'applicazione.
	return FALSE;
}
