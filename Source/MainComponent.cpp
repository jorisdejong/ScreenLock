#include "MainComponent.h"

#include <cstdio>
#include <windows.h>
#include <strsafe.h>
#include <tlhelp32.h>

//==============================================================================
MainComponent::MainComponent() : Thread( "screenlock" )
{
	auto area = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->totalArea;
	setOpaque( false );
	setBounds( area );

	setWantsKeyboardFocus( true );
	addKeyListener( this );

	startThread();
}

MainComponent::~MainComponent()
{
	stopThread( 100 );
}

//==============================================================================
void MainComponent::paint( juce::Graphics& g )
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll( juce::Colours::black.withAlpha( 0.75f ) );

	g.setFont( juce::Font( 48.0f ) );
	g.setColour( juce::Colours::white );
	g.drawText( "LOCKED...", getLocalBounds(), juce::Justification::centred, true );


	toFront( true );
}

void MainComponent::resized()
{
	// This is called when the MainComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.

}

bool MainComponent::keyPressed( const juce::KeyPress& key, juce::Component* originatingComponent )
{


	if ( key == juce::KeyPress( 'u' ) && ( ( unlockSequence.isEmpty() || unlockSequence == "uw" ) ) )
		unlockSequence += "u";
	else if ( key == juce::KeyPress( 'w' ) && unlockSequence == "u" )
		unlockSequence += "w";
	else
		unlockSequence.clear();

	DBG( unlockSequence );

	if ( unlockSequence == "uwu" )
		juce::JUCEApplication::quit();

	return true;
}

void MainComponent::run()
{
	while ( !threadShouldExit() )
	{
		PROCESSENTRY32 entry;
		entry.dwSize = sizeof( PROCESSENTRY32 );

		

		HANDLE snapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL );

		if ( Process32First( snapshot, &entry ) == TRUE )
		{
			while ( Process32Next( snapshot, &entry ) == TRUE )
			{
				if ( stricmp( entry.szExeFile, "Taskmgr.exe" ) == 0 )
				{
					HANDLE hProcess = OpenProcess( PROCESS_TERMINATE, FALSE, entry.th32ProcessID );

					if ( hProcess != NULL )
						TerminateProcess( hProcess, 0 );

					CloseHandle( hProcess );

				}
				
			}
		}

		CloseHandle( snapshot );

		Thread::sleep( 5 );
	}
}
