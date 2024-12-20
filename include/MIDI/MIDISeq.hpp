#pragma once 

enum {
 CMD_PLAYNOTE =  0x90,    /* play a note: low nibble is generator #, note is next byte */
 CMD_STOPNOTE =   0x80,    /* stop a note: low nibble is generator # */
 CMD_RESTART =   0xe0,    /* restart the score from the beginning */
 CMD_INSTRUMENT= 0xc0,
 CMD_STOP =   0xf0
} midi_cmd_k;

#define AMPLITUDE 1.0

static const float velocity2amplitude[] = {0.01778,0.01966,0.02164,0.02371,0.02588,0.02814,0.03049,0.03294,0.03549,0.03812,
                                    0.04086,0.04369,0.04661,0.04963,0.05274,0.05594,0.05924,0.06264,0.06613,0.06972,
                                    0.07340,0.07717,0.08104,0.08500,0.08906,0.09321,0.09746,0.10180,0.10624,0.11077,
                                    0.11539,0.12011,0.12493,0.12984,0.13484,0.13994,0.14513,0.15042,0.15581,0.16128,
                                    0.16685,0.17252,0.17828,0.18414,0.19009,0.19613,0.20227,0.20851,0.21484,0.22126,
                                    0.22778,0.23439,0.24110,0.24790,0.25480,0.26179,0.26887,0.27605,0.28333,0.29070,
                                    0.29816,0.30572,0.31337,0.32112,0.32896,0.33690,0.34493,0.35306,0.36128,0.36960,
                                    0.37801,0.38651,0.39511,0.40381,0.41260,0.42148,0.43046,0.43953,0.44870,0.45796,
                                    0.46732,0.47677,0.48631,0.49595,0.50569,0.51552,0.52544,0.53546,0.54557,0.55578,
                                    0.56609,0.57648,0.58697,0.59756,0.60824,0.61902,0.62989,0.64085,0.65191,0.66307,
                                    0.67432,0.68566,0.69710,0.70863,0.72026,0.73198,0.74380,0.75571,0.76771,0.77981,
                                    0.79201,0.80430,0.81668,0.82916,0.84174,0.85440,0.86717,0.88003,0.89298,0.90602,
                                    0.91917,0.93240,0.94573,0.95916,0.97268,0.98629,1.00000};

static const float tune_frequencies2_PGM[] = {    8.1758,    8.6620,    9.1770,    9.7227,    10.3009,    10.9134,    11.5623,    12.2499,
                                           12.9783,   13.7500,   14.5676,   15.4339,   16.3516,    17.3239,    18.3540,    19.4454,
                                           20.6017,   21.8268,   23.1247,   24.4997,   25.9565,    27.5000,    29.1352,    30.8677,
                                           32.7032,   34.6478,   36.7081,   38.8909,   41.2034,    43.6535,    46.2493,    48.9994,
                                           51.9131,   55.0000,   58.2705,   61.7354,   65.4064,    69.2957,    73.4162,    77.7817,
                                           82.4069,   87.3071,   92.4986,   97.9989,   103.8262,   110.0000,   116.5409,   123.4708,
                                           130.8128,  138.5913,  146.8324,  155.5635,  164.8138,   174.6141,   184.9972,   195.9977,
                                           207.6523,  220.0000,  233.0819,  246.9417,  261.6256,   277.1826,   293.6648,   311.1270,
                                           329.6276,  349.2282,  369.9944,  391.9954,  415.3047,   440.0000,   466.1638,   493.8833,
                                           523.2511,  554.3653,  587.3295,  622.2540,  659.2551,   698.4565,   739.9888,   783.9909,
                                           830.6094,  880.0000,  932.3275,  987.7666,  1046.5023,  1108.7305,  1174.6591,  1244.5079,
                                           1318.5102, 1396.9129, 1479.9777, 1567.9817, 1661.2188,  1760.0000,  1864.6550,  1975.5332,
                                           2093.0045, 2217.4610, 2349.3181, 2489.0159, 2637.0205,  2793.8259,  2959.9554,  3135.9635,
                                           3322.4376, 3520.0000, 3729.3101, 3951.0664, 4186.0090,  4434.9221,  4698.6363,  4978.0317,
                                           5274.0409, 5587.6517, 5919.9108, 6271.9270, 6644.8752,  7040.0000,  7458.6202,  7902.1328,
                                           8372.0181, 8869.8442, 9397.2726, 9956.0635, 10548.0818, 11175.3034, 11839.8215, 12543.8540};


#define NO_MIDI_CMD 0
#define NOTE_OFF 2
#define NOTE_ON 3

typedef struct {
uint32_t cmd;
uint32_t inst;
float amp;
float tune;
} midi_cmd_t;


#define NBSONG 6
static const uint8_t* allSongs[NBSONG]={empire,champion,overture,toccata,pink,bohemian};
static const char* names[NBSONG]={"The Empire strikes back",
"We are the champion",
"Overture",
"Toccata and fugue in D minor",
"Pink Panther",
"Bohemian Rhapsody"};

template<typename OUT,int outputSize>
class MIDISeq;

template<>
class MIDISeq<midi_cmd_t,1>:public NodeBase
{
public:
    MIDISeq(std::initializer_list<FIFOBase<midi_cmd_t>*> dst,char *txt,const uint8_t music[] ):
    mDstList(dst),mytxt(txt),mMusic((const uint8_t*)music){
    	done=false;
        inst = 0;
        mPos=0;
        delayState = false;
        delay=0;
        nb_channels=mDstList.size();
        nbSong=0;
        mMusic = allSongs[nbSong];
        strcpy(mytxt,names[0]);
    };

    int prepareForRunning() final
    {
        if (this->willOverflow())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(CG_SUCCESS);
    };

    int run() final 
    {
        std::vector<midi_cmd_t *> b(nb_channels);
        std::vector<bool> cmdSet(nb_channels);

        //midi_cmd_t *b[nb_channels];
        //bool cmdSet[nb_channels];
        for(int i=0;i<nb_channels;i++)
        {
           b[i]=this->getWriteBuffer(i);
           b[i]->cmd = NO_MIDI_CMD;
           cmdSet[i] = false;
        }
        while (!done)
        {
            if (delayState)
            {
                if (gTime >= delay)
                {
                    //printf("%f %f\n",gTime,delay);

                    delayState=false;
                }
                else 
                {
                    return(CG_SUCCESS);
                }
            }
            uint8_t c = mMusic[mPos];
            mPos+=1;
            if (c == CMD_STOP)
            {
                //printf("Stop all \r\n");
                for(int i=0;i<nb_channels;i++)
                {
                   b[i]->cmd = NOTE_OFF;
                }

                nbSong++;
                //printf("New song\r\n");
                if (nbSong==NBSONG)
                {
                    //printf("Done\r\n");
                    done=true;
                    return(CG_STOP_SCHEDULER);
                }
                mPos=0;
                mMusic = allSongs[nbSong];
                strcpy(mytxt,names[nbSong]);


                delay = gTime + 0.5;
                delayState = true;

                done=false;
                inst = 0;
                mPos=0;

                //done = true;
                return(CG_SUCCESS);
            }

            uint8_t opcode = c & 0xF0;
            uint8_t chan = c & 0x0F;
            if (c < 0x80)
            {
                uint8_t s = mMusic[mPos];
                mPos += 1;
                    
                uint16_t d_time = ((uint16_t)c << 8) | s;
                delay = gTime + (double)d_time/1000.0;
                delayState = true;
                //printf("%d Delay %d %d\r\n",chan,c,s);

                continue;
            }
            if (opcode == CMD_STOPNOTE)
            {
                if (chan < nb_channels)
                {
                   //printf("Stop %d \r\n",chan);
                   if (cmdSet[chan])
                   {
                     return(CG_SUCCESS);
                   }
                    // Off has priority
                   cmdSet[chan] = true;
                   b[chan]->cmd = NOTE_OFF;
                }
                continue;
            }
            if (opcode == CMD_INSTRUMENT)
            {
                inst = mMusic[mPos];
                mPos += 1;
                continue;
            }
            if (opcode == CMD_PLAYNOTE)
            {
                   uint8_t note = mMusic[mPos];
                   mPos += 1;
                       
                   uint8_t velocity = mMusic[mPos];
                   mPos += 1;
                   
                if (chan < nb_channels)
                {
                  
                   if (cmdSet[chan])
                   {
                        return(CG_SUCCESS);
                   }
                   //let amp = AMPLITUDE * velocity2amplitude[Int(velocity)-1]
                   float amp = AMPLITUDE * velocity/255.0;
                       //let tune = tune_frequencies2_PGM[Int(note)]
                   float tune = 440*pow(2.0,((float)note-69.0)/12.0);
   
             
                    cmdSet[chan] = true;
   
                    b[chan]->cmd = NOTE_ON;
                    b[chan]->inst=inst;
                    b[chan]->amp=amp;
                    b[chan]->tune=tune;

                    if (amp == 0)
                    {
                        b[chan]->cmd = NOTE_OFF;
                    }

                    //printf("ON %d %d %f %f\r\n",chan,inst,amp,tune);

                }
                continue;

            }
            if (opcode == CMD_RESTART)
            {
                mPos=0;
                continue;

            }
        }
        
        return(CG_SUCCESS);
    };

protected:
	const uint8_t *mMusic;
    bool delayState;
    double delay ;
	uint32_t mPos;
    bool done;
    uint8_t inst;
    int nbSong;
    int mSong;

    midi_cmd_t * getWriteBuffer(int id=1){return mDstList[id]->getWriteBuffer(1);};
    bool willOverflow(int id=1){return mDstList[id]->willOverflowWith(1);};

private:
    int nb_channels;
    std::vector<FIFOBase<midi_cmd_t>*> mDstList;
    char*mytxt;
};