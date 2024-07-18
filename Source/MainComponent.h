#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
	This component lives inside our window, and this is where you should put all
	your controls and content.
*/
class MainComponent :
	public juce::Component,
	public juce::KeyListener,
	public juce::Thread
{
public:
	//==============================================================================
	MainComponent();
	~MainComponent() override;

	//==============================================================================
	void paint( juce::Graphics& ) override;
	void resized() override;

private:
	//==============================================================================
	// Inherited via KeyListener
	bool keyPressed( const juce::KeyPress& key, juce::Component* originatingComponent ) override;

	juce::String unlockSequence;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( MainComponent )

		

		// Inherited via Thread
		void run() override;

};
