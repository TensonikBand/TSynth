// This optional setting causes Encoder to use more optimized code,
// It must be defined before Encoder.h is included.
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>
#include <Bounce.h>

//Teensy 3.6 - Mux Pins
#define MUX_0 28
#define MUX_1 27
#define MUX_2 26
#define MUX_3 25
#define MUX1_S 38
#define MUX2_S 29
//Mux 1 Connections
#define MUX1_noiseLevel 0
#define MUX1_pitchLfoRate 1
#define MUX1_pitchLfoWaveform 2
#define MUX1_pitchLfoAmount 3
#define MUX1_detune 4
#define MUX1_oscMix 5
#define MUX1_filterAttack 6
#define MUX1_filterDecay 7
#define MUX1_pwmAmountA 8
#define MUX1_waveformA 9
#define MUX1_octaveA 10
#define MUX1_pwmAmountB 11
#define MUX1_waveformB 12
#define MUX1_octaveB 13
#define MUX1_pwmRate 14
#define MUX1_pitchEnv 15
//Mux 2 Connections
#define MUX2_release 0
#define MUX2_sustain 1
#define MUX2_decay 2
#define MUX2_attack 3
#define MUX2_filterLFOAmount 4
#define MUX2_FXMix 5
#define MUX2_FXAmount 6
#define MUX2_glide 7
#define MUX2_filterEnv 8
#define MUX2_filterRelease 9
#define MUX2_filterSustain 10
#define MUX2_filterType 11
#define MUX2_resonance 12
#define MUX2_cutoff 13
#define MUX2_filterLFORate 14
#define MUX2_filterLFOWaveform 15

//Teensy 3.6 Pins
#define OSC_FX_SW 39
#define VCF_LFO_RETRIG_SW 16
#define UNISON_SW 36
#define TEMPO_SW 30
#define RECALL_SW 9
#define SAVE_SW 11
#define MENU_SW 12
#define BACK_SW 10
#define VOLUME_POT A14

#define ENCODER_PINA 4
#define ENCODER_PINB 5

#define RETRIG_LED 34
#define TEMPO_LED 35
#define UNISON_LED 37
#define OSC_FX_LED 14

#define MUXCHANNELS 16
#define QUANTISE_FACTOR 7

#define DEBOUNCE 30

static byte muxInput = 0;
static int mux1ValuesPrev[MUXCHANNELS] = {};
static int mux2ValuesPrev[MUXCHANNELS] = {};

static int mux1Read = 0;
static int mux2Read = 0;
static int volumeRead = 0;
static int volumePrevious = 0;
static long encPrevious = 0;

//These are pushbuttons and require debouncing
Bounce oscFXSwitch = Bounce(OSC_FX_SW, DEBOUNCE);
Bounce vcfLFORetrigSwitch = Bounce(VCF_LFO_RETRIG_SW, DEBOUNCE);
Bounce unisonSwitch = Bounce(UNISON_SW, DEBOUNCE);
Bounce tempoSwitch = Bounce(TEMPO_SW, DEBOUNCE);

Bounce recallButton = Bounce(RECALL_SW, DEBOUNCE); //On encoder
boolean recall = true; //Hack for recall button
Bounce saveButton = Bounce(SAVE_SW, DEBOUNCE);
boolean del = true; //Hack for save button
Bounce menuButton = Bounce(MENU_SW, DEBOUNCE);
boolean reini = true; //Hack for menu button
Bounce backButton = Bounce(BACK_SW, DEBOUNCE);
boolean panic = true; //Hack for back button
Encoder encoder(ENCODER_PINA, ENCODER_PINB);

void setupHardware()
{
  //Mux address pins
  pinMode(MUX_0, OUTPUT);
  pinMode(MUX_1, OUTPUT);
  pinMode(MUX_2, OUTPUT);
  pinMode(MUX_3, OUTPUT);

  //Switches
  pinMode(OSC_FX_SW, INPUT_PULLUP);
  pinMode(VCF_LFO_RETRIG_SW, INPUT_PULLUP);
  pinMode(UNISON_SW, INPUT_PULLUP);
  pinMode(TEMPO_SW, INPUT_PULLUP);
  pinMode(RECALL_SW, INPUT_PULLUP); //On encoder
  pinMode(SAVE_SW, INPUT_PULLUP);
  pinMode(MENU_SW, INPUT_PULLUP);
  pinMode(BACK_SW, INPUT_PULLUP);

  //LEDs
  pinMode(RETRIG_LED, OUTPUT);
  pinMode(TEMPO_LED, OUTPUT);
  pinMode(UNISON_LED, OUTPUT);
  pinMode(OSC_FX_LED, OUTPUT);
}
