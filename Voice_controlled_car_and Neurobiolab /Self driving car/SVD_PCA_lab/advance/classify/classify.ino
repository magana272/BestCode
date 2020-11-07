/*
 * classify.ino
 *
 * EE16B Spring 2016
 * Emily Naviasky & Nathaniel Mailoa
 *
 * EE 16B Fall 2017
 * Andrew Blatner
 *
 */

#define MIC_INPUT                   P6_0

#define SIZE                        2752
#define SIZE_AFTER_FILTER           172
#define ADC_TIMER_MS                0.35

/*---------------------------*/
/*      CODE BLOCK PCA1      */
/*---------------------------*/
#define SNIPPET_SIZE                  80
#define PRELENGTH                     5
#define THRESHOLD                     0.65

// Enveloping and K-means constants
//#define SNIPPET_SIZE                40
//#define PRELENGTH                   5
//#define THRESHOLD                   0.5

#define KMEANS_THRESHOLD            0.05
#define LOUDNESS_THRESHOLD          300

/*---------------------------*/
/*      CODE BLOCK PCA2      */
/*---------------------------*/
float pca_vec1[80] = {-0.0126152065635, -0.0262423365165, -0.0525691279695, -0.0861571673991, -0.0822533727248, -0.111519329309, -0.104030271863, -0.120002126458, -0.0888673644006, -0.102934817119, -0.0883916011066, -0.0996570115435, -0.0451450207736, 0.0223229019462, 0.129257152997, 0.215811272769, 0.241990107379, 0.254028371502, 0.269242018466, 0.281659513064, 0.284203541555, 0.268918548798, 0.241809986623, 0.231820783813, 0.207233757312, 0.159933544867, 0.111584377602, 0.0610992598669, 0.0319007578852, 0.0383362194636, 0.0313409874134, 0.0142315729357, 0.0183702919164, 0.0168720054469, 0.0142095221815, 0.00109266116874, -0.00865002409227, -0.0198146843239, -0.0335951146201, -0.0323437785388, -0.036432359865, -0.0409437992726, -0.0557089688646, -0.0800517056073, -0.0893830333404, -0.096966786981, -0.116750199469, -0.124232341759, -0.124435580295, -0.128027866954, -0.126996650545, -0.124557978743, -0.103282658935, -0.13131292342, -0.0977465666238, -0.0992587120183, -0.100663800496, -0.0884183588064, -0.0717867639373, -0.0714938631065, -0.0625770941447, -0.0532284723566, -0.045122421509, -0.0302751184066, -0.0146330322473, -0.0174508076395, -0.0139059410773, -0.0118394701508, -0.00317607049302, -0.00342787199004, 0.00629755985391, 0.00884678639745, 0.0140329195794, 0.0141281065788, 0.0155268692391, 0.0162095867758, 0.0132182866561, 0.0155582074243, 0.0128728891523, 0.0149152057473};
float pca_vec2[80] = {0.0995411611782, 0.147585995542, 0.144572322076, 0.174212300539, 0.151674396128, 0.198538200473, 0.202330977277, 0.195354713256, 0.140300540449, 0.193093286538, 0.177692568814, 0.186462917389, 0.16044763229, 0.176386698759, 0.201729455242, 0.135177609912, 0.103054575447, 0.0173573927143, 0.0174133550131, -0.0280359010003, -0.0803010597116, -0.080449160634, -0.100326113315, -0.073780287316, -0.0980268015173, -0.0966380644976, -0.0848803349287, -0.0545026962505, -0.0130491088693, -0.0381183122061, -0.00302959920199, 0.0651453352234, 0.0706400962163, 0.0661301386303, 0.096604167499, 0.106578510379, 0.099323254332, 0.109804580199, 0.106437729558, 0.0996531814112, 0.0703675032464, 0.0620215682188, 0.0550227668118, 0.0171664697345, -0.0274612144367, -0.0542723896176, -0.0927122820612, -0.0941690723911, -0.126631050977, -0.15679225317, -0.148405882327, -0.172137404809, -0.153249040045, -0.186365454679, -0.155826997175, -0.146603952948, -0.14667866285, -0.140288456573, -0.124218122956, -0.126842579081, -0.121873109071, -0.128422225632, -0.103567292347, -0.0991620924739, -0.0881211139255, -0.0848730789798, -0.0680254289465, -0.0583642789015, -0.0611988891189, -0.0492078087578, -0.0283486475294, -0.0305731212173, -0.0216101266736, -0.0156391548038, -0.0216019597202, -0.00112257834559, -0.033790508014, -0.0153733067486, -0.00570249065738, -0.00745193308386};
float pca_vec3[80] = {0.1552576379, 0.149699411083, 0.107488301609, 0.0563349578858, -0.041604231534, -0.1178702759, -0.168863350265, -0.258116683918, -0.202553167317, -0.198061503795, -0.183322804266, -0.181175259838, -0.205364796494, -0.126563524924, -0.112727481404, -0.0748920300548, -0.101746373618, -0.11484577796, -0.114999669829, -0.144962938821, -0.114613712316, -0.091130032445, -0.043890890327, -0.0724386928614, -0.0281159391952, -0.00155560521122, 0.0210339952314, 0.0852198220046, 0.129650463866, 0.173884745489, 0.192649195671, 0.253406799161, 0.223374880954, 0.197392633088, 0.190953245651, 0.1631277339, 0.170931179629, 0.165521337179, 0.148157799826, 0.119102772521, 0.102578576184, 0.0852442804529, 0.0596236278208, 0.0262853576951, 0.0255321048604, -0.0223000966624, -0.0554798376776, -0.0688167963962, -0.0909332054964, -0.0789980558939, -0.0909817601584, -0.0789271801761, -0.064749813175, -0.0823725889843, -0.0513955399316, -0.0516223522154, -0.0644465328024, -0.0636676342198, -0.0366122512013, -0.0417150005324, -0.0204303816811, 0.00126428787631, -0.000160854780052, 0.0256650457248, 0.0268528565481, 0.029372152367, 0.0368746580288, 0.0284117838612, 0.0555951802108, 0.0382197291694, 0.0264397645978, 0.0535098487501, 0.0439965851034, 0.0461347283552, 0.0546481696271, 0.0200191049808, 0.0744310201404, 0.0387207845393, 0.0297417999725, 0.0306762647625};
float projected_mean_vec[3] = {0.0127925801857, 0.058742476634, -0.0623530141228};
float centroid1[3] = {-0.0262739567545, 0.0499968831178, 0.013232561019};
float centroid2[3] = {0.063324283732, 0.00275184159186, -0.0286483234141};
float centroid3[3] = {0.0305512578017, -0.0207575220104, 0.0297087649433};
float centroid4[3] = {-0.0639601374536, -0.0293790511879, -0.0207771234767};

//float pca_vec1[SNIPPET_SIZE] = ;
//float pca_vec2[SNIPPET_SIZE] = ;
//float projected_mean_vec[2] = ;
//float centroid1[2] = ;
//float centroid2[2] = ;
//float centroid3[2] = ;
//float centroid4[2] = ;
//float* centroids[4] = {
//  (float *) &centroid1, (float *) &centroid2,
//  (float *) &centroid3, (float *) &centroid4
//};

/*---------------------------*/
/*---------------------------*/
/*---------------------------*/

float result[SNIPPET_SIZE] = {0};
float proj1 = 0;
float proj2 = 0;
float proj3 = 0;

// Data array and index pointer
int re[SIZE] = {0};
volatile int re_pointer = 0;

/*---------------------------*/
/*       Norm functions      */
/*---------------------------*/

// Compute the L2 norm of (dim1, dim2) and centroid
// input: dim1: 1st dimension coordinate
//        dim2: 2nd dimension coordinate
//        centroid: size-2 array containing centroid coordinates
// output: L2 norm (Euclidean distance) between point and centroid
float l2_norm(float dim1, float dim2, float* centroid) {
  return sqrt(pow(dim1-centroid[0],2) + pow(dim2-centroid[1],2));
}

// Compute the L2 norm of (dim1, dim2, dim3) and centroid
// input: dim1: 1st dimension coordinate
//        dim2: 2nd dimension coordinate
//        dim3: 3rd dimension coordinate
//        centroid: size-3 array containing centroid coordinates
// output: L2 norm (Euclidean distance) between point and centroid
float l2_norm3(float dim1, float dim2, float dim3, float* centroid) {
  return sqrt(pow(dim1-centroid[0],2) + pow(dim2-centroid[1],2) + pow(dim3-centroid[2],2));
}

void setup(void) {
  Serial.begin(38400);

  pinMode(MIC_INPUT, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  re_pointer = 0;
  reset_blinker();
  setTimer();
}

void loop(void) {
  if (re_pointer == SIZE) {
    digitalWrite(RED_LED, LOW);

    // Apply enveloping function and get snippet with speech.
    // Do classification only if loud enough.
    if (envelope(re, result)) {

      // Reset projection result variables declared above
      proj1 = 0;
      proj2 = 0;
      proj3 = 0;

      /*---------------------------*/
      /*      CODE BLOCK PCA3      */
      /*---------------------------*/

      // Project 'result' onto the principal components
      // Hint: 'result' is an array
      // Hint: do this entire operation in 1 loop by replacing the '...'
      // YOUR CODE HERE
      for (int i = 0; i < SNIPPET_SIZE; i++) {
          proj1 += result[i] * pca_vec1[i];
          proj2 += result[i] * pca_vec2[i];
          proj3 += result[i] * pca_vec3[i];
      }

      // Demean the projection
      proj1 -= projected_mean_vec[0];
      proj2 -= projected_mean_vec[1];
      proj3 -= projected_mean_vec[2];

      // Classification
      // Use the function 'l2_norm' defined above
      // ith centroid: 'centroids[i]'
      float best_dist = 999999;
      int best_index = -1;
      // YOUR CODE HERE
      Serial.println(result[20]);
             Serial.println(proj1);
             
             Serial.println(proj2);
             
             Serial.println(proj3);
      float dist[] = {l2_norm3(proj1,proj2,proj3,centroid1), l2_norm3(proj1,proj2,proj3,centroid2), l2_norm3(proj1,proj2,proj3,centroid3), l2_norm3(proj1,proj2,proj3,centroid4)};
      for (int i = 0; i < 4; i++) {
        if (dist[i] < best_dist) {
          best_dist = dist[i];
          best_index = i;
        }
      }     


      // Compare 'best_dist' against the 'KMEANS_THRESHOLD' and print the result
      // If 'best_dist' is less than the 'KMEANS_THRESHOLD', the recording is a word
      // Otherwise, the recording is noise
      // YOUR CODE HERE
      
        Serial.println(dist[0]);
        Serial.println(dist[1]);
        Serial.println(dist[2]);
        Serial.println(dist[3]);
      if (best_dist < KMEANS_THRESHOLD) {
        Serial.println(best_index);
      } else {
        Serial.println("Noise");
      }


      /*---------------------------*/
      /*---------------------------*/
      /*---------------------------*/
    }
    else {
      Serial.println("Below LOUDNESS_THRESHOLD.");
    }


    delay(2000);
    re_pointer = 0;
  }
}

// Enveloping function with thresholding and normalizing,
// returns snippet of interest (containing speech)
bool envelope(int* data, float* data_out) {
  int32_t avg = 0;
  float maximum = 0;
  int32_t total = 0;
  int block;

  // Apply enveloping filter while finding maximum value
  for (block = 0; block < SIZE_AFTER_FILTER; block++) {
    avg = 0;
    for (int i = 0; i < 16; i++) {
      avg += data[i+block*16];
    }
    avg = avg >> 4;
    data[block] = abs(data[block*16] - avg);
    for (int i = 1; i < 16; i++) {
      data[block] += abs(data[i+block*16] - avg);
    }
    if (data[block] > maximum) {
      maximum = data[block];
    }
  }

  // If not loud enough, return false
  if (maximum < LOUDNESS_THRESHOLD) {
    return false;
  }

  // Determine threshold
  float thres = THRESHOLD * maximum;

  // Figure out when interesting snippet starts and write to data_out
  block = PRELENGTH;
  while (data[block++] < thres);
  if (block > SIZE_AFTER_FILTER - SNIPPET_SIZE) {
    block = SIZE_AFTER_FILTER - SNIPPET_SIZE;
  }
  for (int i = 0; i < SNIPPET_SIZE; i++) {
    data_out[i] = data[block-PRELENGTH+i];
    total += data_out[i];
  }

  // Normalize data_out
  for (int i = 0; i < SNIPPET_SIZE; i++) {
    data_out[i] = data_out[i] / total;
  }

  return true;
}

/*---------------------------*/
/*     Helper functions      */
/*---------------------------*/

void reset_blinker(void) {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(RED_LED, HIGH);
  delay(100);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  delay(100);
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  delay(100);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  delay(100);
  digitalWrite(GREEN_LED, LOW);
}

/*---------------------------*/
/*    Interrupt functions    */
/*---------------------------*/

// ISR for timestep
#pragma vector=TIMER2_A0_VECTOR    // Timer A ISR
__interrupt void Timer2_A0_ISR(void) {
  if (re_pointer < SIZE) {
    digitalWrite(RED_LED, HIGH);
    re[re_pointer] = (analogRead(MIC_INPUT) >> 4) - 128;
    re_pointer += 1;
  }
}

// Set timer for timestep; use A2 since A0 & A1 are used by PWM
void setTimer(void) {
  // Set the timer based on 25MHz clock
  TA2CCR0 = (unsigned int) (25000*ADC_TIMER_MS);
  TA2CCTL0 = CCIE;
  __bis_SR_register(GIE);
  TA2CTL = TASSEL_2 + MC_1 + TACLR + ID_0;
}
