
#include "stdafx.h"
// <code>
#include <iostream>
#include <speechapi_cxx.h>
using namespace std;

using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

void recognize_from_file() {
	//auto config = SpeechConfig::FromSubscription("e776a7bfcae64eae8e6a930595ec2809", "eastus");
	//auto audioInput = AudioConfig::FromWavFileInput("https://youtu.be/gCWqPVCuov4");
	//auto recognizer = SpeechRecognizer::FromConfig(config, audioInput);

	//auto result = recognizer->RecognizeOnceAsync().get();
	//cout << "RECOGNIZED: Text=" << result->Text << std::endl;
	cout << "Hello there";
}
int main() {
	recognize_from_file();
}
