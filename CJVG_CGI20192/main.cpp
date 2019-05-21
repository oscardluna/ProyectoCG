/*---------------------------------------------------------*/
/* ----------------   Proyecto --------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*------------- Alumnos: 
					- Durón Luna Oscar  ---------------
					- Vázquez García Carlos Jonathan  ---------------


*/
//#define STB_IMAGE_IMPLEMENTATION
#include <vector>
#include <iostream>
#include <fstream>

#include <glew.h>
#include <glfw3.h>
#include <stb_image.h>

#include "camera.h"
#include "Model.h"

// Other Libs
#include "SOIL2/SOIL2.h"

//
#include <Windows.h>
#include <MMSystem.h>


void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void myData(void);
void draw(Shader, glm::mat4, unsigned int);
void drawBuildind(Shader, glm::mat4, bool*);
void drawTable(Shader, glm::mat4 );
void display(Shader, Shader, Shader, Model, Model, Model, Model, std::vector<Model>, Model, Model);
void getResolution(void);
void animate(void);
void LoadTextures(void);
unsigned int generateTextures(char*, bool);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;

//Camera
Camera camera(glm::vec3(80.76f, 12.25f, -102.04f));

double	lastX = 0.0f,
		lastY = 0.0f;
bool firstMouse = true;

//Timing
double	deltaTime = 0.0f,
		lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(10.0f, 30.0f, 5.0f);
glm::vec3 lightDirection(1.0f, -1.0f, -1.0f);

//For Keyboard
float	movX = 0.0f,
		movY = 0.0f,
		movZ = -5.0f,
		rotX = 0.0f;

//Texture
unsigned int	t_edificio,
				t_cristal,
				t_white,
				t_roca,
				t_panda,
				t_metal,
				t_arbusto,
				t_cesped,
				t_parota,
				t_brick,
				t_central,
				q;

float rotLetrero = 0.0f;
float translateLet = 0.0f;
float rotLetrero2 = 0.0f;
bool animateLetrero = false;

//Contruction
			// Escalas
float		escalaAltura = 1.0f,
			escalaAnchura = 1.0f,
			escalaProfundidad = 1.0f;

			// Colunma Frente
float		numCol = 2.0f,
			anchoCol = 0.5f,
			altoCol = 80.0f,
			profCol = 1.0f;

			// Piso Enfrente
float		numPiso = 5.0f,
			altoPiso = 1.0f,
			anchoPiso = 30.0f,
			profPiso = 65.0f;

			// Banca
float		anchoBanca = anchoPiso * 0.75,
			altoBanca = altoPiso * 3,
			profBanca = altoBanca;


			//Ventana Frente
float		altoVentana = (altoCol - (numPiso - 2) * altoPiso * escalaAltura) / (numPiso - 1),
			anchoVentana = (anchoPiso - numCol * anchoCol * escalaAnchura) / (numCol - 1),
			profVentana = 0.05f;

			//Pared lateral
float		altoPared = altoCol,
			anchoParedLateral = anchoCol,
			profParedLateral = profPiso;

			//Pared fron
float		anchoParedP = profPiso - 2 * profCol,
			profParedP = anchoCol,
			anchoPared = anchoPiso - 2 * anchoCol,
			profPared = profCol;

			// Escalera
float		anchoEscalera = anchoPared / 2,
			altoEscalera = (altoVentana + altoPiso) / 2,
			profEscalera = profPiso / 2;

			// Escalón
float		anchoEscalon = anchoEscalera,
			altoEscalon = 0.0f,
			profEscalon = 0.0f;

			// Division
float		anchoDivision = anchoVentana,
			altoDivision = altoVentana,
			profDivision = 0.2f;

			// Salón
float		anchoSalon = 0.0f,
			altoSalon= 0.0f,
			profSalon= 0.0f;


float escX, escY, escZ;

float trasX, trasY, trasZ;
float diffX, diffZ;

glm::vec3 puertaPos( 0.0f, 0.0f, 0.0f);


std::string s = "";
const std::string delimiter = ",";

#define MAX_P_FRAMES 350
#define MAX_O_FRAMES 250

float	posX = 0.0f,
		posY = 0.0f,
		posZ = 0.0f,
		rotRodIzq = 0.0f,
		movBrazo = 0.0f,
		movBrazoDer = 0.0f,
		giroMonito = 0.0f,
		rotOvni = 0.0f,
		rotOvniY = 0.0f,
		rotOvniZ = 0.0f,
		ovniX = 0.0f,
		ovniY = 0.0f,
		ovniZ = 0.0f;



unsigned int velocidadAnim = 5;

// Variable animación personaje

int i_max_steps = 10;
int i_curr_steps = 0;
int i = 0;


typedef struct personaje_frame{
	float posX;	
	float posY;	
	float posZ;	
	float incX;		
	float incY;		
	float incZ;		
	float rotRodIzq;
	float rotInc;
	float giroMonito;
	float giroMonitoInc;
	float movBrazo;
	float movBrazoInc; 
	float movBrazoDer;
	float movBrazoDerInc;

}P_FRAME;

P_FRAME PersonajeFrame[MAX_P_FRAMES];
int FrameIndex = 0;
bool play = false;
int playIndex = 0;

// Variables animacíón ovni

int i_max_steps_ovni = 30;
int i_curr_steps_ovni = 0;

typedef struct ovni_frame {
	float posX;		
	float posY;		
	float posZ;		
	float incX;		
	float incY;		
	float incZ;
	float rotY;
	float rotYinc;
	float rotZ;
	float rotZinc;

}O_FRAME;

O_FRAME OvniFrame[MAX_O_FRAMES];
int FrameIndexO = 0;
bool playO = false;
int playIndexO = 0;


float val(float n){
	if(n > 0)
		return 1.0f;
	if(n < 0)
		return -1.0f;
	if(n == 0)
		return 0.0f;
}

float mov(float esp, float esc,float tam) {
	return esp * esc * 2 + tam * (esp/abs(esp));
}

glm::vec3 scale(float x, float y, float z){
	x = x/escX; y = y/escY; z = z/escZ;
	escX = x*escX; escY = y*escY; escZ = z*escZ;
	return glm::vec3( x, y, z);
}

glm::vec3 translate(float x, float y, float z){
	float a,b,c;
	a = abs(x)/2 + escX/2;  b = abs(y)/2 + escY/2;  c = abs(z)/2 + escZ/2;
	a = a/escX; b = b/escY; c = c/escZ;
	return glm::vec3( a * val(x), b * val(y), c * val(z));
}

void saveFrame(void){

	printf("frameindex %d\n", FrameIndexO);

	std::ofstream out;
	out.open("animacionOvni.txt", std::ofstream::out | std::ofstream::app);
	s = to_string(FrameIndexO++) + "," + to_string(ovniX) + "," + to_string(ovniY) + "," + to_string(ovniZ) + "," + to_string(rotOvniY) + "," + to_string(rotOvniZ) + "\n";
	out << s;
	out.close();

}

void loadAnimationPer(void) {

	std::ifstream in;
	std::string str;
	std::string cad = "";
	std::string token;
	size_t pos = 0, i;
	float val;

	in.open("animacionPer.txt");
	getline(in, str);
	do {
		cad = str;
		i = 0;

		while ((pos = cad.find(delimiter)) != std::string::npos) {
			token = cad.substr(0, pos);
			val = stof(token);
			switch (i){
				case 0:
					FrameIndex = val;
					break;
				case 1:
					PersonajeFrame[FrameIndex].posX = val;
					break;
				case 2:
					PersonajeFrame[FrameIndex].posY = val;
					break;
				case 3:
					PersonajeFrame[FrameIndex].posZ = val;
					break;
				case 4:
					PersonajeFrame[FrameIndex].rotRodIzq = val;
					break;
				case 5:
					PersonajeFrame[FrameIndex].giroMonito = val;
					break;
				case 6:
					PersonajeFrame[FrameIndex].movBrazo = val;
					break;
				case 7:
					PersonajeFrame[FrameIndex].movBrazoDer = val;
					break;
				default:
					break;
			}

			cad.erase(0, pos + delimiter.length());
			i++;
		}

		FrameIndex++;
		printf("%s\n", str.c_str());
	} while (getline(in, str));

	in.close();

}

void loadAnimationOvni(void) {

	std::ifstream in;
	std::string str;
	std::string cad = "";
	std::string token;
	size_t pos = 0, i;
	float val;

	in.open("animacionOvni.txt");
	getline(in, str);
	do {
		cad = str;
		i = 0;

		while ((pos = cad.find(delimiter)) != std::string::npos) {
			token = cad.substr(0, pos);
			val = stof(token);
			switch (i) {
			case 0:
				FrameIndexO = val;
				break;
			case 1:
				OvniFrame[FrameIndexO].posX = val;
				break;
			case 2:
				OvniFrame[FrameIndexO].posY = val;
				break;
			case 3:
				OvniFrame[FrameIndexO].posZ = val;
				break;
			case 4:
				OvniFrame[FrameIndexO].rotY = val;
				break;
			case 5:
				OvniFrame[FrameIndexO].rotZ = val;
				break;
			default:
				break;
			}

			cad.erase(0, pos + delimiter.length());
			i++;
		}

		FrameIndex++;
		printf("%s\n", str.c_str());
	} while (getline(in, str));

	in.close();

}


void resetElements(void){

	posX = PersonajeFrame[0].posX;
	posY = PersonajeFrame[0].posY;
	posZ = PersonajeFrame[0].posZ;

	rotRodIzq = PersonajeFrame[0].rotRodIzq;
	giroMonito = PersonajeFrame[0].giroMonito;
	movBrazo = PersonajeFrame[0].movBrazo;
	movBrazoDer = PersonajeFrame[0].movBrazoDer;
}

void resetElementsO(void) {

	ovniX = OvniFrame[0].posX;
	ovniY = OvniFrame[0].posY;
	ovniZ = OvniFrame[0].posZ;

	rotOvniY = OvniFrame[0].rotY;
	rotOvniZ = OvniFrame[0].rotZ;

}


void interpolationP(void){

	PersonajeFrame[playIndex].incX = (PersonajeFrame[playIndex + 1].posX - PersonajeFrame[playIndex].posX) / i_max_steps;
	PersonajeFrame[playIndex].incY = (PersonajeFrame[playIndex + 1].posY - PersonajeFrame[playIndex].posY) / i_max_steps;
	PersonajeFrame[playIndex].incZ = (PersonajeFrame[playIndex + 1].posZ - PersonajeFrame[playIndex].posZ) / i_max_steps;

	PersonajeFrame[playIndex].rotInc = (PersonajeFrame[playIndex + 1].rotRodIzq - PersonajeFrame[playIndex].rotRodIzq) / i_max_steps;
	PersonajeFrame[playIndex].giroMonitoInc = (PersonajeFrame[playIndex + 1].giroMonito - PersonajeFrame[playIndex].giroMonito) / i_max_steps;
	PersonajeFrame[playIndex].movBrazoInc = (PersonajeFrame[playIndex + 1].movBrazo - PersonajeFrame[playIndex].movBrazo) / i_max_steps;
	PersonajeFrame[playIndex].movBrazoDerInc = (PersonajeFrame[playIndex + 1].movBrazoDer - PersonajeFrame[playIndex].movBrazoDer) / i_max_steps;

}

void interpolationO(void) {

	OvniFrame[playIndexO].incX = (OvniFrame[playIndexO + 1].posX - OvniFrame[playIndexO].posX) / i_max_steps_ovni;
	OvniFrame[playIndexO].incY = (OvniFrame[playIndexO + 1].posY - OvniFrame[playIndexO].posY) / i_max_steps_ovni;
	OvniFrame[playIndexO].incZ = (OvniFrame[playIndexO + 1].posZ - OvniFrame[playIndexO].posZ) / i_max_steps_ovni;

	OvniFrame[playIndexO].rotYinc = (OvniFrame[playIndexO + 1].rotY - OvniFrame[playIndexO].rotY) / i_max_steps_ovni;
	OvniFrame[playIndexO].rotZinc = (OvniFrame[playIndexO + 1].rotZ - OvniFrame[playIndexO].rotZ) / i_max_steps_ovni;

}


unsigned int generateTextures(const char* filename, bool alfa){
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	
	unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data){
		if (alfa)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		return textureID;
	}
	else{
		std::cout << "Failed to load texture" << std::endl;
		return 100;
	}

	stbi_image_free(data);
}

void getResolution(){
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;

	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

}

void LoadTextures(){
	t_edificio = generateTextures("Texturas/Stone3.png", 0);
	t_cristal = generateTextures("Texturas/crystal.jpg", 0);
	t_white = generateTextures("Texturas/white.jpg", 0);
	t_roca = generateTextures("Texturas/roca.jpg", 0);
	t_metal = generateTextures("Texturas/Metal2.jpg", 0);
	t_arbusto = generateTextures("Texturas/Q.jpg", 0);
	t_cesped = generateTextures("Texturas/Brick.jpg", 0);
	t_parota = generateTextures("Texturas/parota.jpg", 0);
	q = generateTextures("Texturas/Q.jpg", 0);
	// bind textures on corresponding texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, t_edificio);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, t_cristal);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, t_white);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, t_roca);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, t_metal);
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, t_arbusto);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, t_cesped);
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, t_parota);
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, t_brick);
	glActiveTexture(GL_TEXTURE10);
	glBindTexture(GL_TEXTURE_2D, q);
	glActiveTexture(GL_TEXTURE11);
	glBindTexture(GL_TEXTURE_2D, t_central);
}

void myData(){
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,


		//////Segunda caja

		-0.5f, -0.5f, 0.5f,		0.0f,  0.0f,  1.0f,  	0.25f, 0.33f,	//V0 - Frontal
		0.5f, -0.5f, 0.5f,		0.0f,  0.0f,  1.0f,		0.5f, 0.33f,	//V1
		0.5f, 0.5f, 0.5f,		0.0f,  0.0f,  1.0f,		0.5f, 0.66f,	//V5
		-0.5f, 0.5f, 0.5f,		0.0f,  0.0f,  1.0f,		0.25f, 0.66f,	//V4

		0.5f, -0.5f, -0.5f,		0.0f,  0.0f,  -1.0f,	1.0f, 0.33f,	//V2 - Trasera
		-0.5f, -0.5f, -0.5f,	0.0f,  0.0f,  -1.0f,	0.75f, 0.33f,	//V3
		-0.5f, 0.5f, -0.5f,		0.0f,  0.0f,  -1.0f,	0.75f, 0.66f,	//V7
		0.5f, 0.5f, -0.5f,		0.0f,  0.0f,  -1.0f,	1.0f, 0.66f, 	//V6

		-0.5f, 0.5f, 0.5f,		-1.0f,  0.0f,  0.0f,	0.25f, 0.66f, 	//V4 - Izq
		-0.5f, 0.5f, -0.5f,		-1.0f,  0.0f,  0.0f,	0.0f, 0.66f,	//V7
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 0.33f,	//V3
		-0.5f, -0.5f, 0.5f,		-1.0f,  0.0f,  0.0f,	0.25f, 0.33f, 	//V0

		0.5f, 0.5f, 0.5f,		1.0f,  0.0f,  0.0f,		0.5f, 0.66f,	//V5 - Der
		0.5f, -0.5f, 0.5f,		1.0f,  0.0f,  0.0f,		0.5f, 0.33f,	//V1
		0.5f, -0.5f, -0.5f,		1.0f,  0.0f,  0.0f,		0.75f, 0.33f,	//V2
		0.5f, 0.5f, -0.5f,		1.0f,  0.0f,  0.0f,		0.75f, 0.66f,	//V6

		-0.5f, 0.5f, 0.5f,		0.0f,  1.0f,  0.0f,		0.25f, 1.0f,	//V4 - Sup
		0.5f, 0.5f, 0.5f,		0.0f,  1.0f,  0.0f,		0.5f, 1.0f, 	//V5
		0.5f, 0.5f, -0.5f,		0.0f,  1.0f,  0.0f,		0.5f, 0.66f,	//V6
		-0.5f, 0.5f, -0.5f,		0.0f,  1.0f,  0.0f,		0.25f, 0.66f,	//V7

		-0.5f, -0.5f, 0.5f,		0.0f,  -1.0f,  0.0f,	0.25f, 0.33f, 	//V0 - Inf
		-0.5f, -0.5f, -0.5f,	0.0f,  -1.0f,  0.0f,	0.25f, 0.0, 	//V3
		0.5f, -0.5f, -0.5f,		0.0f,  -1.0f,  0.0f,	0.5f, 0.0f, 	//V2
		0.5f, -0.5f, 0.5f,		0.0f,  -1.0f,  0.0f,	0.5f, 0.33f 	//V1


	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

}

void animateP(void) {
	if (play) {
		if (i_curr_steps >= i_max_steps) { //end of animation between frames?
			playIndex++;
			if (playIndex > FrameIndex - 2) {	//end of total animation?
				printf("termina animacion Personaje\n");
				playIndex = 0;
				play = false;
			}
			else { //Next frame interpolations
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolationP();
			}
		}
		else {
			//Draw animation
			posX += PersonajeFrame[playIndex].incX;
			posY += PersonajeFrame[playIndex].incY;
			posZ += PersonajeFrame[playIndex].incZ;

			rotRodIzq += PersonajeFrame[playIndex].rotInc;
			giroMonito += PersonajeFrame[playIndex].giroMonitoInc;
			movBrazo += PersonajeFrame[playIndex].movBrazoInc;
			movBrazoDer += PersonajeFrame[playIndex].movBrazoDerInc;

			i_curr_steps++;
		}
	}

}

void animateO(void) {
	if (playO) {
		if (i_curr_steps_ovni >= i_max_steps_ovni) { //end of animation between frames?
			playIndexO++;
			if (playIndexO > FrameIndexO - 2) {	//end of total animation?
				printf("termina animacion Ovni\n");
				playIndexO = 0;
				playO = false;
			}
			else { //Next frame interpolations
				i_curr_steps_ovni = 0; //Reset counter
								  //Interpolation
				interpolationO();
			}
		}
		else {
			//Draw animation
			ovniX += OvniFrame[playIndexO].incX;
			ovniY += OvniFrame[playIndexO].incY;
			ovniZ += OvniFrame[playIndexO].incZ;

			rotOvniY += OvniFrame[playIndexO].rotYinc;
			rotOvniZ += OvniFrame[playIndexO].rotZinc;

			i_curr_steps_ovni++;
		}
	}

}


void animate(void){
	//if (play)

	diffX = posX - puertaPos.x;
	diffZ = posZ + profPiso/2 - puertaPos.z;
	diffX = abs(diffX);
	diffZ = abs(diffZ);

	if ( (diffX <= 2*anchoPiso && diffX >= -2*anchoPiso) && (diffZ <= profPiso  && diffZ >= -profPiso)){
		if (rotX > -172.5f) {
			rotX -= 2.5f;
		}else
			rotX = -175.0f;
	}
	else
		if (rotX < -2.5f) {
			rotX += 2.5f;
		}
		else
			rotX = 0.0f;

	rotOvni += 2.5f;

	if (animateLetrero) {
		if (rotLetrero <= 90)
		{
			rotLetrero += 2.0f;
		}
		else {
			if (translateLet <= 19.0f) {
				translateLet += 0.8f;
				
				/*rotLetrero = 0.0f;
				translateLet = 0.0f;*/
			}
			else
			{
				if (rotLetrero2 <= 90.0f) {
					rotLetrero2 += 15.0f;
				}
				else
				{
					animateLetrero = false;
				}
			}
		}
	}
}

void draw( Shader s, glm::mat4 m, unsigned int i) {
	s.setMat4("model", m);
	s.setInt("material_diffuse", i);
	glDrawArrays(GL_QUADS, 24, 24);
}

void drawBuildind(Shader shader, glm::mat4 model, bool* requisito) {
	
	float	anchoPuerta;

	if (altoEscalera > profEscalera) {
		altoEscalon = altoEscalera / profEscalera;
		profEscalon = (profEscalera / altoEscalera) * 4;
	}
	else {
		profEscalon = profEscalera / altoEscalera;
		altoEscalon = (altoEscalera / profEscalera) * 4;
	}

	float cuenta;

	glm::mat4 tmp0 = glm::mat4(1.0f);
	glm::mat4 tmp1 = glm::mat4(1.0f);
	glm::mat4 tmp2 = glm::mat4(1.0f);

	///////////////////////////////////////////////  COLUMNAS ///////////////////////////////////////////////  
	/// ENFRENTE
	/// Izquierda

	// Escala inicial
	escX = anchoCol; escY = altoCol; escZ = profCol;
	// Posición inicial
	trasX = -(anchoPiso / 2 - anchoCol / 2); trasY = 0.0f; trasZ = 0.0f;

	model = glm::translate(model, translate(trasX, trasY, trasZ));
	model = glm::scale(model, glm::vec3(anchoCol, altoCol, profCol));
	draw(shader, model, t_edificio);

	tmp1 = model;
	if (requisito[0]) {
		model = glm::translate(model, translate(anchoPared, 0.0f, 0.0f));
		trasX = escX; trasY = escY; trasZ = escZ;
		model = glm::scale(model, scale(anchoPared, altoPared, profPared));
		draw(shader, model, t_edificio);
		escX = trasX; escY = trasY; escZ = trasZ;
		trasY = 0.0f; trasZ = 0.0f;
	}

	i = 1;
	while (i < numCol) {
		trasX = mov(anchoVentana, escalaAnchura, anchoCol);
		model = glm::translate(tmp1, translate(trasX, trasY, trasZ));
		tmp0 = model = glm::scale(model, scale(anchoCol, altoCol, profCol));
		draw(shader, model, t_edificio);
		i++;
	}

	tmp1 = model;
	if (requisito[1]) {
		model = glm::translate(model, translate(0.0f, 0.0f, -anchoParedP));
		trasX = escX; trasY = escY; trasZ = escZ;
		model = glm::scale(model, scale(anchoCol, altoPared, anchoParedP));
		draw(shader, model, t_edificio);
		escX = trasX; escY = trasY; escZ = trasZ;
		trasY = 0.0f; trasZ = 0.0f;
	}

	//// ATRÄS	
	// Derecha
	trasX = 0.0f;
	trasZ = mov(-(profPiso - 2 * profCol), escalaProfundidad, profCol);
	model = glm::translate(tmp1, translate(trasX, trasY, trasZ));
	tmp2 = model = glm::scale(model, scale(anchoCol, altoCol, profCol));
	draw(shader, model, t_edificio);

	tmp1 = model;
	if (requisito[2]) {
		requisito[6] = false;
		model = glm::translate(model, translate(-anchoPared, 0.0f, 0.0f));
		trasX = escX; trasY = escY; trasZ = escZ;
		model = glm::scale(model, scale(anchoPared, altoPared, profPared));
		draw(shader, model, t_edificio);
		escX = trasX; escY = trasY; escZ = trasZ;
		trasY = 0.0f; trasZ = 0.0f;
	}
	
	trasZ = 0.0f;
	i = 1;
	while (i < numCol) {
		trasX = mov(-anchoVentana, escalaAnchura, anchoCol);
		model = glm::translate(tmp1, translate(trasX, trasY, trasZ));
		model = glm::scale(model, scale(anchoCol, altoCol, profCol));
		draw(shader, model, t_edificio);
		i++;
	}

	if (requisito[3]) {
		model = glm::translate(model, translate(0.0f, 0.0f, anchoParedP));
		trasX = escX; trasY = escY; trasZ = escZ;
		model = glm::scale(model, scale(anchoCol, altoPared, anchoParedP));
		draw(shader, model, t_edificio);
		escX = trasX; escY = trasY; escZ = trasZ;
		trasY = 0.0f; trasZ = 0.0f;
	}


	/////////////////////////////////////////////  PISOS ///////////////////////////////////////////////  

	//// ARRIBA
	trasX = -(anchoPiso - 2 * anchoCol);
	trasY = altoPiso;
	trasZ = -(profPiso - 2 * profCol);
	model = glm::translate(tmp0, translate(trasX, trasY, trasZ));
	model = glm::scale(model, scale(anchoPiso, altoPiso, profPiso));
	draw(shader, model, t_edificio);

	i = 1;
	while (i < numPiso) {
		float var0, var1, var2;

		trasX = 0.0;
		trasY = mov(-(altoVentana), escalaAltura, altoPiso);
		trasZ = 0.0;
		model = glm::translate(model, translate(trasX, trasY, trasZ));
		tmp1 = model = glm::scale(model, scale(anchoPiso, altoPiso, profPiso));
		draw(shader, model, t_edificio);

		//// Escaleras
		if (requisito[6]) {

			float p = 0.0f,
			trasX = escX; trasY = escY; trasZ = escZ;
			cuenta = 0.0f;

			model = glm::translate(model, translate(0.0f, 0.0f, -0.0001f));
			model = glm::scale(model, scale(0.0001f, 0.0001f, 0.0001f));

			model = glm::translate(model, translate(anchoEscalon, 0.0f, 0.0f));
			model = glm::scale(model, scale(anchoEscalon, altoEscalon, profEscalon));
			draw(shader, model, t_edificio);
			cuenta += altoEscalon;

			while (cuenta < altoEscalera) {
				model = glm::translate(model, translate(0.0f, altoEscalon, -profEscalon));
				model = glm::scale(model, scale(anchoEscalon, altoEscalon, profEscalon));
				draw(shader, model, t_edificio);
				p += profEscalon;
				cuenta += altoEscalon;
			}

			model = glm::translate(model, translate(-0.0001f, 0.0f, 0.0f));
			model = glm::scale(model, scale(0.0001f, 0.0001f, 0.0001f));

			tmp0 = model;

			var0 = escX; var1 = escY; var2 = escZ;
			model = glm::translate(model, translate(0.0f, 0.0f, -profEscalera / 2));
			model = glm::scale(model, scale(anchoPared, altoEscalon, profEscalera / 2));
			draw(shader, model, t_edificio);
			p += profEscalera / 2;
			escX = var0; escY = var1; escZ = var2;

			model = glm::translate(tmp0, translate(-anchoEscalon, 0.0f, 0.0f));
			model = glm::scale(model, scale(anchoEscalon, altoEscalon, profEscalon));
			draw(shader, model, t_edificio);

			while (cuenta < altoEscalera*2) {
				model = glm::translate(model, translate(0.0f, altoEscalon, profEscalon));
				model = glm::scale(model, scale(anchoEscalon, altoEscalon, profEscalon));
				draw(shader, model, t_edificio);
				cuenta += altoEscalon;
			}

			escX = anchoCol; escY = altoCol; escZ = profCol;
			model = glm::translate(tmp2, translate(0.0f, 0.0f, -p));
			model = glm::scale(model, scale(anchoCol, altoCol, p));
			draw(shader, model, t_edificio);
			model = glm::translate(model, translate(-anchoPared, 0.0f, -anchoCol));
			model = glm::scale(model, scale(anchoPared, altoCol, anchoCol));
			draw(shader, model, t_edificio);
			model = glm::translate(model, translate(-anchoCol, 0.0f, p));
			model = glm::scale(model, scale(anchoCol, altoCol, p));
			draw(shader, model, t_edificio);


			escX = trasX; escY = trasY; escZ = trasZ;
			model = tmp1;
		}

		// Ventanas
		if (requisito[4]) {
			trasX = escX; trasY = escY; trasZ = escZ;
			// Puerta?
			if (i == (numPiso - 1) && requisito[5]) {
				
				anchoPuerta = (anchoVentana - (anchoCol / 2)) / 2;

				model = glm::translate(tmp1, translate(0.0f, 0.0001f, 0.0001f));
				model = glm::scale(model, scale(0.0001f, 0.0001f, 0.0001f));
				draw(shader, model, t_edificio);

				model = glm::translate(model, translate( -anchoPuerta*2, altoVentana, 0.0f));
				model = glm::rotate(model, glm::radians(rotX), glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::translate(model, translate(anchoPuerta, 0.0f, 0.0f));
				model = glm::scale(model, scale(anchoPuerta, altoVentana, profVentana));
				draw(shader, model, t_cristal);
				escX = trasX; escY = trasY; escZ = trasZ;

				model = glm::translate(tmp1, translate(0.0f, 0.0001f, 0.0001f));
				model = glm::scale(model, scale(0.0001f, 0.0001f, 0.0001f));
				draw(shader, model, t_edificio);

				model = glm::translate(model, translate( anchoPuerta * 2, altoVentana, 0.0f));
				model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::rotate(model, glm::radians(-rotX), glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::translate(model, translate(anchoPuerta, 0.0f, 0.0f));
				model = glm::scale(model, scale(anchoPuerta, altoVentana, profVentana));
				draw(shader, model, t_cristal);

				model = tmp1;
				break;
			}
			model = glm::translate(model, translate(0.0f, altoVentana, profVentana));
			model = glm::scale(model, scale(anchoVentana - anchoCol / 2, altoVentana, profVentana));
			draw(shader, model, t_cristal);

			escX = trasX; escY = trasY; escZ = trasZ;
			model = tmp1;
		}

		// PuertaS
		if (requisito[5] && !requisito[4]) {
			trasX = escX; trasY = escY; trasZ = escZ;

			anchoPuerta = (anchoVentana - (anchoCol / 2)) / 2;

			model = glm::translate(tmp1, translate(0.0f, 0.0001f, 0.0001f));
			model = glm::scale(model, scale(0.0001f, 0.0001f, 0.0001f));

			model = glm::translate(model, translate(-anchoPuerta * 2, altoVentana, 0.0f));
			model = glm::rotate(model, glm::radians(rotX), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::translate(model, translate(anchoPuerta, 0.0f, 0.0f));
			model = glm::scale(model, scale(anchoPuerta, altoVentana, profVentana));
			draw(shader, model, t_cristal);
			escX = trasX; escY = trasY; escZ = trasZ;

			model = glm::translate(tmp1, translate(0.0f, 0.0001f, 0.0001f));
			model = glm::scale(model, scale(0.0001f, 0.0001f, 0.0001f));

			model = glm::translate(model, translate(anchoPuerta * 2, altoVentana, 0.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(-rotX), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::translate(model, translate(anchoPuerta, 0.0f, 0.0f));
			model = glm::scale(model, scale(anchoPuerta, altoVentana, profVentana));
			draw(shader, model, t_cristal);

			escX = trasX; escY = trasY; escZ = trasZ;
			model = tmp1;
		}


		i++;
	}
	model = tmp1;
}

void drawTable(Shader shader, glm::mat4 model) {



	float	altoMesa = 0.5f,
			anchoMesa = 7.5f,
			profMesa = 18.0f;
	float	altoPata = 5.0f,
			anchoPata = 0.5f,
			profPata = 0.5f;

	float var0, var1, var2;

	glm::mat4 tmp0 = glm::mat4(1.0f);

	// Escala inicial
	var0 = escX; var1 = escY; var2 = escZ;


		model = glm::translate(model, translate(0, 0.0f, -profMesa));
		model = glm::scale(model, scale(anchoPata, altoPata, profPata));
		draw(shader, model, t_metal);

		model = glm::translate(model, translate(0.0f, 0.0f, 2 * profMesa));
		model = glm::scale(model, scale(anchoPata, altoPata, profPata));
		draw(shader, model, t_metal);

		model = glm::translate(model, translate(-2 * anchoMesa, 0.0f, 0.0f));
		model = glm::scale(model, scale(anchoPata, altoPata, profPata));
		draw(shader, model, t_metal);

		model = glm::translate(model, translate(0.0f, 0.0f, -2 * profMesa));
		model = glm::scale(model, scale(anchoPata, altoPata, profPata));
		draw(shader, model, t_metal);

		model = glm::translate(model, translate(-0.0001f, 0.0001f, -0.0001f));
		model = glm::scale(model, scale(0.0001f, 0.0001f, 0.0001f));

		model = glm::translate(model, translate(anchoMesa + anchoPata, altoMesa, profMesa + profPata));
		model = glm::scale(model, scale(anchoMesa + 2 * anchoPata, altoMesa, profMesa + 2 * profPata));
		draw(shader, model, t_parota);

	escX = var0; escY = var1; escZ = var2;
}

void drawBanca(Shader lightShader, glm::mat4 model) {


	// Escala inicial
	escX = anchoBanca; escY = altoBanca; escZ = profBanca;

	// Posición inicial
	trasX = -anchoPiso / 4; trasY = -(altoCol / 2) + profBanca / 2; trasZ = anchoPiso * 2.5;

	model = glm::translate(glm::mat4(1.0f), glm::vec3(trasX, trasY, trasZ));
	model = glm::scale(model, glm::vec3(anchoBanca, altoBanca, profBanca));
	draw(lightShader, model, t_roca);

	model = glm::translate(model, translate(0.0001f, 0.0f, -0.0001f));
	model = glm::scale(model, scale(0.0001f, 0.0001f, 0.0001f));

	model = glm::translate(model, translate(-profBanca, 0.0f, -anchoBanca));
	model = glm::scale(model, scale(profBanca, altoBanca, anchoBanca));
	draw(lightShader, model, t_roca);

	model = glm::translate(model, translate(-0.0001f, 0.0f, -0.0001f));
	model = glm::scale(model, scale(0.0001f, 0.0001f, 0.0001f));

	model = glm::translate(model, translate(-anchoBanca, 0.0f, profBanca));
	model = glm::scale(model, scale(anchoBanca, altoBanca, profBanca));
	draw(lightShader, model, t_roca);

	model = glm::translate(model, translate(-0.0001f, 0.0f, 0.0001f));
	model = glm::scale(model, scale(0.0001f, 0.0001f, 0.0001f));

	model = glm::translate(model, translate(profBanca, 0.0f, anchoBanca));
	model = glm::scale(model, scale(profBanca, altoBanca, anchoBanca));
	draw(lightShader, model, t_roca);

	// Escala inicial
	escX = anchoBanca; escY = altoBanca; escZ = profBanca;
	trasX = anchoPiso * 1.25; trasZ = anchoPiso * 3;

	model = glm::translate(glm::mat4(1.0f), glm::vec3(trasX, trasY, trasZ));
	model = glm::scale(model, glm::vec3(anchoBanca / 2, altoBanca, profBanca));
	draw(lightShader, model, t_roca);

	model = glm::translate(model, translate(0.0001f, 0.0f, -0.0001f));
	model = glm::scale(model, scale(0.0001f, 0.0001f, 0.0001f));

	model = glm::translate(model, translate(profBanca, 0.0f, anchoBanca / 2));
	model = glm::scale(model, scale(profBanca, altoBanca, anchoBanca / 2));
	draw(lightShader, model, t_roca);

	model = glm::translate(model, translate(-0.0001f, 0.0f, 0.0001f));
	model = glm::scale(model, scale(0.0001f, 0.0001f, 0.0001f));

	model = glm::translate(model, translate(anchoBanca, 0.0f, profBanca));
	model = glm::scale(model, scale(anchoBanca, altoBanca, profBanca));
	draw(lightShader, model, t_roca);

	i = 0;
	while (i < 5) {
		model = glm::translate(model, translate(anchoBanca, 0.0f, 0.0f));
		model = glm::scale(model, scale(anchoBanca, altoBanca, profBanca));
		draw(lightShader, model, t_roca);
		i++;
	}

	trasZ = anchoBanca / 2;

	model = glm::translate(model, translate(0.0f, -0.1f, trasZ));
	model = glm::scale(model, scale(anchoBanca, 0.1f, trasZ));
	draw(lightShader, model, t_cesped);

	model = glm::translate(model, translate(0.0f, altoBanca, profBanca));
	model = glm::scale(model, scale(anchoBanca, altoBanca, profBanca));
	draw(lightShader, model, t_roca);


	model = glm::translate(model, translate(-anchoBanca, 0.0f, 0.0f));
	model = glm::scale(model, scale(anchoBanca, altoBanca, profBanca));
	draw(lightShader, model, t_roca);

	model = glm::translate(model, translate(0.0f, -0.1f, -trasZ));
	model = glm::scale(model, scale(anchoBanca, 0.1f, trasZ));
	draw(lightShader, model, t_cesped);

	model = glm::translate(model, translate(-anchoBanca, 0.0f, 0.0f));
	model = glm::scale(model, scale(anchoBanca, 0.1f, trasZ));
	draw(lightShader, model, t_cesped);

	model = glm::translate(model, translate(0.0f, altoBanca, profBanca));
	model = glm::scale(model, scale(anchoBanca, altoBanca, profBanca));
	draw(lightShader, model, t_roca);


	model = glm::translate(model, translate(-anchoBanca, 0.0f, 0.0f));
	model = glm::scale(model, scale(anchoBanca, altoBanca, profBanca));
	draw(lightShader, model, t_roca);

	model = glm::translate(model, translate(0.0f, -0.1f, -trasZ));
	model = glm::scale(model, scale(anchoBanca, 0.1f, trasZ));
	draw(lightShader, model, t_cesped);

	model = glm::translate(model, translate(-anchoBanca, 0.0f, 0.0f));
	model = glm::scale(model, scale(anchoBanca, 0.1f, trasZ));
	draw(lightShader, model, t_cesped);

	model = glm::translate(model, translate(0.0f, altoBanca, profBanca));
	model = glm::scale(model, scale(anchoBanca, altoBanca, profBanca));
	draw(lightShader, model, t_roca);

	model = glm::translate(model, translate(-anchoBanca, 0.0f, 0.0f));
	model = glm::scale(model, scale(anchoBanca, altoBanca, profBanca));
	draw(lightShader, model, t_roca);

	model = glm::translate(model, translate(0.0f, -0.1f, -trasZ));
	model = glm::scale(model, scale(anchoBanca, 0.1f, trasZ));
	draw(lightShader, model, t_cesped);

	model = glm::translate(model, translate(-anchoBanca, 0.0f, 0.0f));
	model = glm::scale(model, scale(anchoBanca, 0.1f, trasZ));
	draw(lightShader, model, t_cesped);

	model = glm::translate(model, translate(0.0f, 0.0f, -trasZ));
	model = glm::scale(model, scale(anchoBanca, 0.1f, trasZ));
	draw(lightShader, model, t_cesped);

	model = glm::translate(model, translate(0.0f, 0.0f, trasZ));
	model = glm::scale(model, scale(anchoBanca, 0.1f, trasZ));
	draw(lightShader, model, t_cesped);

	model = glm::translate(model, translate(0.0f, altoBanca, profBanca));
	model = glm::scale(model, scale(anchoBanca, altoBanca, profBanca));
	draw(lightShader, model, t_roca);

	model = glm::translate(model, translate(-anchoBanca, 0.0f, 0.0f));
	model = glm::scale(model, scale(anchoBanca, altoBanca, profBanca));
	draw(lightShader, model, t_roca);

	model = glm::translate(model, translate(0.0f, -0.1f, -trasZ));
	model = glm::scale(model, scale(anchoBanca, 0.1f, trasZ));
	draw(lightShader, model, t_cesped);

	i = 0;
	while (i < 9) {
		model = glm::translate(model, translate(0.0f, 0.0f, -trasZ));
		model = glm::scale(model, scale(anchoBanca, 0.1f, trasZ));
		draw(lightShader, model, t_cesped);
		i++;
	}

	model = glm::translate(model, translate(-anchoBanca, 0.0f, 0.0f));
	model = glm::scale(model, scale(anchoBanca, 0.1f, trasZ));
	draw(lightShader, model, t_cesped);

	i = 0;
	while (i < 9) {
		model = glm::translate(model, translate(0.0f, 0.0f, trasZ));
		model = glm::scale(model, scale(anchoBanca, 0.1f, trasZ));
		draw(lightShader, model, t_cesped);
		i++;
	}

	model = glm::translate(model, translate(0.0f, altoBanca, profBanca));
	model = glm::scale(model, scale(anchoBanca, altoBanca, profBanca));
	draw(lightShader, model, t_roca);

	model = glm::translate(model, translate(-anchoBanca, 0.0f, 0.0f));
	model = glm::scale(model, scale(anchoBanca, altoBanca, profBanca));
	draw(lightShader, model, t_roca);


	model = glm::translate(model, translate(0.0f, -0.1f, -trasZ));
	model = glm::scale(model, scale(anchoBanca, 0.1f, trasZ));
	draw(lightShader, model, t_cesped);

	i = 0;
	while (i < 9) {
		model = glm::translate(model, translate(0.0f, 0.0f, -trasZ));
		model = glm::scale(model, scale(anchoBanca, 0.1f, trasZ));
		draw(lightShader, model, t_cesped);
		i++;
	}


	model = glm::translate(model, translate(-anchoBanca, 0.0f, 0.0f));
	model = glm::scale(model, scale(anchoBanca, 0.1f, trasZ));
	draw(lightShader, model, t_cesped);

	i = 0;
	while (i < 9) {
		model = glm::translate(model, translate(0.0f, 0.0f, trasZ));
		model = glm::scale(model, scale(anchoBanca, 0.1f, trasZ));
		draw(lightShader, model, t_cesped);
		i++;
	}

	model = glm::translate(model, translate(-anchoBanca, 0.0f, 0.0f));
	model = glm::scale(model, scale(anchoBanca, 0.1f, trasZ));
	draw(lightShader, model, t_cesped);

	i = 0;
	while (i < 9) {
		model = glm::translate(model, translate(0.0f, 0.0f, -trasZ));
		model = glm::scale(model, scale(anchoBanca, 0.1f, trasZ));
		draw(lightShader, model, t_cesped);
		i++;
	}


	model = glm::translate(model, translate(-anchoBanca / 2, 0.0f, 0.0f));
	model = glm::scale(model, scale(anchoBanca / 2, 0.1f, trasZ));
	draw(lightShader, model, t_cesped);

	i = 0;
	while (i < 9) {
		model = glm::translate(model, translate(0.0f, 0.0f, trasZ));
		model = glm::scale(model, scale(anchoBanca / 2, 0.1f, trasZ));
		draw(lightShader, model, t_cesped);
		i++;
	}

}

void display(Shader lightShader, Shader modelShader, Shader spotShader, Model compu, Model nivel,  Model lamp, Model ovni, std::vector<Model> Personaje, Model arbol, Model enterprise) {


	bool requisito[7] = { false, false, false, false, false, false, false };

	lightShader.use();

	lightShader.setVec3("light.direction", lightDirection);
	lightShader.setVec3("viewPos", camera.Position);
	lightShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	lightShader.setVec3("light.diffuse", 0.8f, 0.8f, 0.8f);
	lightShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
	lightShader.setFloat("material_shininess", 32.0f);

	// create transformations and Projection
	glm::mat4 tmp0 = glm::mat4(1.0f);
	glm::mat4 tmp1 = glm::mat4(1.0f);
	glm::mat4 tmp2 = glm::mat4(1.0f);
	glm::mat4 tmp3 = glm::mat4(1.0f);

	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

	float var, var0, var1, var2;

	//Use "projection" to include Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
	view = camera.GetViewMatrix();

	// pass them to the shaders
	lightShader.setMat4("model", model);
	lightShader.setMat4("view", view);
	lightShader.setMat4("projection", projection);

	glBindVertexArray(VAO);

	lightShader.setVec3("ambientColor", 0.0f, 0.0f, 0.0f);
	lightShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

	requisito[0] = false; // Pared frontal?
	requisito[1] = false; // Pared lateral derecha?
	requisito[2] = false; // Pared lateral izquierda?
	requisito[3] = false; // Pared trasera
	requisito[4] = true; // Ventanas?
	requisito[5] = true; // Puerta?
	requisito[6] = true; // Escaleras?

	////////////////////////////////////////////////////// EDIFICIO CENTRAL //////////////////////////////////////////////////////

	// Centro
	drawBuildind(lightShader, model, requisito);
	requisito[5] = false;
	requisito[6] = false;

	// Derecha
	requisito[2] = true;
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3((anchoPiso - 1), 0.0f, 0.0f));
	drawBuildind(lightShader, model, requisito);

	// Izquierda
	requisito[2] = true;
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-(anchoPiso - 1), 0.0f, 0.0f));
	drawBuildind(lightShader, model, requisito);

	////////////////////////////////////////////////////// EDIFICIO IZQUIERDA //////////////////////////////////////////////////////

	//Centro
	requisito[4] = false;
	requisito[5] = true;
	model = glm::translate(model, glm::vec3(-(anchoPiso / 2) - profCol , 0.0f,  -profPiso/2 ));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	drawBuildind(lightShader, model, requisito);
	requisito[4] = true;
	requisito[5] = false;

	tmp0 = model;

	var = anchoPiso - 1;

	// Izquierda atrás
	model = glm::translate(model, glm::vec3( var, 0.0f, 0.0f));
	drawBuildind(lightShader, model, requisito);

	model = glm::translate(model, glm::vec3(var, 0.0f, 0.0f));
	drawBuildind(lightShader, model, requisito);

	requisito[1] = true;
	model = glm::translate(model, glm::vec3(var, 0.0f, 0.0f));
	drawBuildind(lightShader, model, requisito);
	requisito[1] = false;
	requisito[0] = false;

	// Izquierda enfrente
	model = glm::translate(tmp0, glm::vec3( -var, 0.0f, 0.0f));
	drawBuildind(lightShader, model, requisito);

	model = glm::translate(model, glm::vec3(-var, 0.0f, 0.0f));
	drawBuildind(lightShader, model, requisito);

	model = glm::translate(model, glm::vec3(-var, 0.0f, 0.0f));
	drawBuildind(lightShader, model, requisito);

	model = glm::translate(model, glm::vec3(-var, 0.0f, 0.0f));
	drawBuildind(lightShader, model, requisito);

	requisito[3] = true;
	model = glm::translate(model, glm::vec3(-var, 0.0f, 0.0f));
	drawBuildind(lightShader, model, requisito);
	requisito[3] = false;

	////////////////////////////////////////////////////// EDIFICIO DERECHA //////////////////////////////////////////////////////

	// Centro
	model = tmp0;
	requisito[4] = false;
	requisito[5] = true;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, ( anchoPiso - 1.0f) * 3.08f ));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	drawBuildind(lightShader, model, requisito);
	requisito[4] = true;
	requisito[5] = false;

	tmp1 = model;

	// Derecha atrás
	model = glm::translate(model, glm::vec3(-var, 0.0f, 0.0f));
	drawBuildind(lightShader, model, requisito);

	model = glm::translate(model, glm::vec3(-var, 0.0f, 0.0f));
	drawBuildind(lightShader, model, requisito);

	tmp0 = model = glm::translate(model, glm::vec3(-var, 0.0f, 0.0f));
	drawBuildind(lightShader, model, requisito);

	tmp0 = model = glm::translate(tmp0, glm::vec3(-var, 0.0f, 0.0f));
	drawBuildind(lightShader, model, requisito);


	tmp0 = model = glm::translate(tmp0, glm::vec3(-var, 0.0f, 0.0f));
	drawBuildind(lightShader, model, requisito);

	// ----------------------------------------------------------------------------------------------- PISO 2 DERECHA -----------------------------------------------------------------------------------------------

	// Escala inicial
	escX = 0.0001f; escY = 0.0001f; escZ = 0.0001f;

	model = glm::translate(model, translate(0.0f, 0.0001f, 0.0f));
	model = glm::scale(model, glm::vec3(0.0001f, 0.0001f, 0.0001f));
	draw(lightShader, model, t_cristal);

	model = glm::translate(model, translate(0.0f, altoVentana, 0.0f));
	model = glm::scale(model, scale(anchoDivision, altoDivision, profDivision));

	var = (profPiso - profCol) / 8;
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, translate(-profDivision, 0.0f, -var));
	model = glm::scale(model, scale(profDivision, altoDivision, var));
	draw(lightShader, model, t_cristal);


	// ----------------------------------------------------------------------------------------------- SALÓN -----------------------------------------------------------------------------------------------


	var = (profPiso - profCol) * 7 / 8;

	anchoSalon = anchoDivision;
	altoSalon = altoDivision;
	profSalon = var;

	float	profPas = profSalon * 2 / 5,
			pasCen = profSalon / 5,
			anchoPas = anchoSalon*2 / 5;

	model = glm::translate(model, translate(0.0f, 0.0f, -var));
	tmp2 = model = glm::scale(model, scale(profDivision, altoDivision, var));
	draw(lightShader, model, t_cristal);

	trasX = escX; trasY = escY; trasZ = escZ;
		model = glm::translate(tmp2, translate(profDivision, 0.0f, 0.0f));
		model = glm::scale(model, scale(profDivision, altoDivision/2, profSalon/2));
		draw(lightShader, model, t_white);
	escX = trasX; escY = trasY; escZ = trasZ;

	model = glm::translate(tmp2, translate(anchoDivision, 0.0f, profDivision));
	model = glm::scale(model, scale(anchoDivision, altoDivision, profDivision));
	draw(lightShader, model, t_cristal);

	model = glm::translate(model, translate(var, 0.0f, 0.0f));
	tmp2 = model = glm::scale(model, scale(var, altoDivision, profDivision));
	draw(lightShader, model, t_cristal);

	trasX = escX; trasY = escY; trasZ = escZ;
	
		model = glm::translate(model, translate(0.0001f, -0.0001f, -0.0001f));
		model = glm::scale(model, scale(0.0001f, 0.0001f, 0.0001f));

		model = glm::translate(model, translate(-4.0f, 2.0f, -profPas));
		model = glm::scale(model, scale(4.0f, 2.0f, profPas));

		model = glm::translate(model, translate(0.0f, 0.0f, -pasCen));
		model = glm::scale(model, scale(1.0f, 1.0f, pasCen));

		model = glm::translate(model, translate(0.0f, 0.0f, -profPas));
		model = glm::scale(model, scale(4.0f, 2.0f, profPas));

		model = glm::translate(model, translate(-0.0001f, 0.0001f, 0.0f));
		model = glm::scale(model, scale(0.0001f, 0.0001f, 0.0001f));

		drawTable(lightShader, model);

		model = glm::translate(model, translate(-anchoPas*3, 0.0f, 0.0f));
		drawTable(lightShader, model);

		model = glm::translate(model, translate(-anchoPas * 3, 0.0f, 0.0f));
		drawTable(lightShader, model);

		model = glm::translate(model, translate(-anchoPas * 3, 0.0f, 0.0f));
		drawTable(lightShader, model);

		model = glm::translate(model, translate(-anchoPas * 2.5, 0.0f, 0.0f));
		drawTable(lightShader, model);

		model = glm::translate(model, translate(anchoPas * 2.5, 0.0f, profPas * 3));
		drawTable(lightShader, model);

		model = glm::translate(model, translate(anchoPas * 3, 0.0f, 0.0f));
		drawTable(lightShader, model);

		model = glm::translate(model, translate(anchoPas * 3, 0.0f, 0.0f));
		drawTable(lightShader, model);

		tmp3 = model = glm::translate(model, translate(anchoPas * 3, 0.0f, 0.0f));
		drawTable(lightShader, model);
	
		var0 = escX; var1 = escY; var2 = escZ;
	
	escX = trasX; escY = trasY; escZ = trasZ;

	var = (profPiso - profCol) / 8;
	model = glm::translate(tmp2, translate(var, 0.0f, 0.0f));
	model = glm::scale(model, scale(var, altoDivision, profDivision));

	var = (profPiso - profCol) * 7 / 8;
	model = glm::translate(model, translate(profDivision, 0.0f, -var));
	model = glm::scale(model, scale(profDivision, altoDivision, var));
	draw(lightShader, model, t_cristal);

	// ----------------------------------------------------------------------------------------------- FIN SALÓN -----------------------------------------------------------------------------------------------

	var = (profPiso - profCol) * 7 / 12;
	model = glm::translate(model, translate(var, 0.0f, profDivision));
	model = glm::scale(model, scale(var, altoDivision, profDivision));
	draw(lightShader, model, t_cristal);

	var = (profPiso - profCol)/2 ;
	model = glm::translate(model, translate(var, 0.0f, 0.0f));
	model = glm::scale(model, scale(var, altoDivision, profDivision));

	var = (profPiso - profCol) * 7 / 8;
	model = glm::translate(model, translate(profDivision, 0.0f, -var));
	model = glm::scale(model, scale(profDivision, altoDivision, var));
	draw(lightShader, model, t_cristal);

	var = (profPiso - profCol) ;
	model = glm::translate(model, translate(var, 0.0f, profDivision));
	model = glm::scale(model, scale(var, altoDivision, profDivision));
	draw(lightShader, model, t_cristal);

	// ----------------------------------------------------------------------------------------------- FIN PISO 2 DERECHA -----------------------------------------------------------------------------------------------

	var = anchoPiso - 1;

	model = glm::translate(tmp0, glm::vec3(-var, 0.0f, 0.0f));
	drawBuildind(lightShader, model, requisito);

	requisito[3] = true;
	model = glm::translate(model, glm::vec3(-var, 0.0f, 0.0f));
	drawBuildind(lightShader, model, requisito);
	requisito[3] = false;
	requisito[0] = false;

	// Derecha enfrente
	model = glm::translate(tmp1, glm::vec3(var, 0.0f, 0.0f));
	drawBuildind(lightShader, model, requisito);

	model = glm::translate(model, glm::vec3(var, 0.0f, 0.0f));
	drawBuildind(lightShader, model, requisito);

	requisito[1] = true;
	model = glm::translate(model, glm::vec3(var, 0.0f, 0.0f));
	drawBuildind(lightShader, model, requisito);
	requisito[1] = false;

	////////////////////////////////////////////////////// BANCAS AFUERA //////////////////////////////////////////////////////

	drawBanca(lightShader,model);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(46.5f, -13.5f, 69.5f));
	model = glm::rotate(model, glm::radians(0.0f + rotLetrero), glm::vec3(0.0f, 0.0f, -1.0f));
	model = glm::translate(model, glm::vec3(3.5f, 3.5f, 0.0f));
	model = glm::translate(model, glm::vec3(translateLet, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(3.5f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotLetrero2), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(7.0f, 7.0f, 0.0f));
/*
	lightShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);*/
	lightShader.setInt("material_diffuse", t_arbusto);
	lightShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 4);

	




	////////////////////////////////////////////////////// MODELOS //////////////////////////////////////////////////////

	modelShader.use();
	modelShader.setMat4("projection", projection);
	modelShader.setMat4("view", view);
	modelShader.setMat4("model", model);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -(altoCol / 2) - altoPiso, -anchoPiso * 2));
	model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
	modelShader.setMat4("model", model);
	nivel.Draw(modelShader);

	//------------------------------------------------------Arbol--------------------------------------------------------
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, -(altoCol / 2) - altoPiso, anchoPiso * 2 + 3));
	model = glm::scale(model, glm::vec3(2.50f, 2.5f, 2.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelShader.setMat4("model", model);
	arbol.Draw(modelShader);

	escX = var0; escY = var1; escZ = var2;

	// ----------------------------------------------------------- Computadoras -----------------------------------------------------------
	model = glm::translate(tmp3, translate(0.0f, 5.5f, 10.5f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	model = glm::rotate(model, glm::radians(90.0f),glm::vec3(0.0f, 1.0f, 0.0f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(10.0f, 0.0f, 0.0f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(10.0f, 0.0f, 0.0f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(45.0f, 0.0f, 0.0f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(10.0f, 0.0f, 0.0f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(10.0f, 0.0f, 0.0f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(0.0f, 0.0f, -35.0f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(-10.0f, 0.0f, 0.0f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(-10.0f, 0.0f, 0.0f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(-45.0f, 0.0f, 0.0f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(-10.0f, 0.0f, 0.0f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(-10.0f, 0.0f, 0.0f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(0.0f, 0.0f, -35.0f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(10.0f, 0.0f, 0.0f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(10.0f, 0.0f, 0.0f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(45.0f, 0.0f, 0.0f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(10.0f, 0.0f, 0.0f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(10.0f, 0.0f, 0.0f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(0.0f, 0.0f, -35.0f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(-10.0f, 0.0f, 0.0f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(-10.0f, 0.0f, 0.0f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(-45.0f, 0.0f, 0.0f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(-10.0f, 0.0f, 0.0f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(-10.0f, 0.0f, 0.0f));
	model = glm::scale(model, scale(0.2f, 0.2f, 0.2f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	model = glm::translate(model, translate(80.0f, 0.0f, -45.0f));
	model = glm::scale(model, scale(0.3f, 0.3f, 0.3f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelShader.setMat4("model", model);
	compu.Draw(modelShader);

	var = - (altoCol / 2) - altoPiso;
	// ----------------------------------------------------------- Lámparas -----------------------------------------------------------
	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, var, anchoPiso * 4));
	model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
	modelShader.setMat4("model", model);
	lamp.Draw(modelShader);
	model = glm::translate(glm::mat4(1.0f), glm::vec3(40.0f, var, anchoPiso * 4));
	model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
	modelShader.setMat4("model", model);
	lamp.Draw(modelShader);
	model = glm::translate(glm::mat4(1.0f), glm::vec3(80.0f, var, anchoPiso * 4));
	model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
	modelShader.setMat4("model", model);
	lamp.Draw(modelShader);
	model = glm::translate(glm::mat4(1.0f), glm::vec3(120.0f, var, anchoPiso * 4));
	model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
	modelShader.setMat4("model", model);
	lamp.Draw(modelShader);

	var = altoCol/2;
	// ----------------------------------------------------------- Ovni -----------------------------------------------------------
	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, var - altoPiso, anchoPiso * 2));
	tmp0 = model = glm::translate(model, glm::vec3(ovniX, ovniY, ovniZ));
	model = glm::rotate(model, glm::radians(rotOvniY), glm::vec3(1.0f, 0.0f, 1.0f));
	model = glm::rotate(model, glm::radians(rotOvni), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	modelShader.setMat4("model", model);
	ovni.Draw(modelShader);

	// ----------------------------------------------------------- Personaje -----------------------------------------------------------
	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -var + 2*altoPiso, 0.0f));
	model = glm::translate(model, glm::vec3(posX, posY, posZ));
	tmp0 = model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
	tmp0 = model = glm::rotate(model, glm::radians(giroMonito), glm::vec3(0.0f, 1.0f, 0.0));
	modelShader.setMat4("model", model);
	Personaje[0].Draw(modelShader);

	//Pierna Der
	model = glm::translate(tmp0, glm::vec3(-0.5f, 0.0f, -0.1f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::rotate(model, glm::radians(-rotRodIzq), glm::vec3(1.0f, 0.0f, 0.0f));
	modelShader.setMat4("model", model);
	Personaje[1].Draw(modelShader);

	//Pie Der
	model = glm::translate(model, glm::vec3(0, -0.9f, -0.2f));
	modelShader.setMat4("model", model);
	Personaje[2].Draw(modelShader);

	//Pierna Izq
	model = glm::translate(tmp0, glm::vec3(0.5f, 0.0f, -0.1f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotRodIzq), glm::vec3(1.0f, 0.0f, 0.0f));
	modelShader.setMat4("model", model);
	Personaje[3].Draw(modelShader);

	//Pie Iz
	model = glm::translate(model, glm::vec3(0, -0.9f, -0.2f));
	modelShader.setMat4("model", model);
	Personaje[2].Draw(modelShader);	//Izq trase

	//Brazo derecho
	model = glm::translate(tmp0, glm::vec3(0.0f, -1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-0.75f, 2.5f, 0));
	model = glm::rotate(model, glm::radians(-movBrazo + movBrazoDer), glm::vec3(1.0f, 0.0f, 0.0f));
	modelShader.setMat4("model", model);
	Personaje[4].Draw(modelShader);

	//Brazo izquierdo
	model = glm::translate(tmp0, glm::vec3(0.0f, -1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.75f, 2.5f, 0));
	model = glm::rotate(model, glm::radians(movBrazo), glm::vec3(1.0f, 0.0f, 0.0f));
	modelShader.setMat4("model", model);
	Personaje[5].Draw(modelShader);

	//Cabeza
	model = glm::translate(tmp0, glm::vec3(0.0f, -1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::translate(model, glm::vec3(0.0f, 2.5f, 0));
	modelShader.setMat4("model", model);
	Personaje[6].Draw(modelShader);

}

int main(){
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Proyecto_CGIHC20192", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwSetWindowPos(window, 0, 30);
    glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, my_input);
    glfwSetFramebufferSizeCallback(window, resize);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//To Enable capture of our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	LoadTextures();
	myData();
	glEnable(GL_DEPTH_TEST);

	Shader posShader("shaders/shader_texture_light_pos.vs", "shaders/shader_texture_light_pos.fs"); //Positional
	Shader lightingShader("shaders/shader_texture_light_dir.vs", "shaders/shader_texture_light_dir.fs"); //Directional
	Shader spotShader("shaders/shader_texture_light_spot.vs", "shaders/shader_texture_light_spot.fs"); //Spotlight
	Shader lampShader("shaders/shader_lamp.vs", "shaders/shader_lamp.fs");

	Shader modelShader("Shaders/modelLoading.vs", "Shaders/modelLoading.fs");

	// Load models
	std::vector<Model> Personaje;

	Model torso = ((char*)"Models/Personaje/torso.obj");
	Personaje.push_back(torso);
	Model piernaDer = ((char*)"Models/Personaje/piernader.obj");
	Personaje.push_back(piernaDer);
	Model botaDer = ((char*)"Models/Personaje/bota.obj");
	Personaje.push_back(botaDer);
	Model piernaIzq = ((char*)"Models/Personaje/piernader.obj");
	Personaje.push_back(piernaIzq);
	Model brazoDer = ((char*)"Models/Personaje/brazoder.obj");
	Personaje.push_back(brazoDer);
	Model brazoIzq = ((char*)"Models/Personaje/brazoizq.obj");
	Personaje.push_back(brazoIzq);
	Model cabeza = ((char*)"Models/Personaje/cabeza.obj");
	Personaje.push_back(cabeza);

	Model compu = ((char *)"Models/Compu/PC12.obj");
	Model pisoModel = ((char *)"Models/piso/piso.obj");
	Model lamp = ((char*)"Models/Lampara/Lampara-obj.obj");
	Model ovni = ((char*)"Models/ovni/ovni-obj.obj");

	Model arbol = ((char *)"Models/arbol/Lowpoly_tree_sample.obj");
	Model enterprise = ((char *)"Models/hola/untitled.obj");
	//Inicialización de PersonajeFrames

	for (int i = 0; i < MAX_P_FRAMES; i++){
		PersonajeFrame[i].incX = 0;
		PersonajeFrame[i].incY = 0;
		PersonajeFrame[i].incZ = 0;
		PersonajeFrame[i].rotInc = 0;
		PersonajeFrame[i].movBrazoInc = 0;
		PersonajeFrame[i].movBrazoDerInc = 0;
	}

    
	// render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window)){
		// per-frame time logic
		// --------------------
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
        // input
        // -----
        //my_input(window);
		animate();
		i = 0;
		while (i < velocidadAnim) {
			animateP();
			animateO();
			i++;
		}


        // render
        // Backgound color
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		display(lightingShader, modelShader, spotShader, compu, pisoModel, lamp, ovni, Personaje, arbol, enterprise);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode){
	// Cámara
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		camera.Position.x = 31.07f;
		camera.Position.y = -16.43f;
		camera.Position.z = 52.73f;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		camera.Position.x = 6.18f;
		camera.Position.y = 606.32f;
		camera.Position.z = 188.29f;
		camera.Pitch = -59.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		camera.Position.x = 127.0f;
		camera.Position.y = -27.0f;
		camera.Position.z = 123.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
		camera.Position.x = 80.76f;
		camera.Position.y = 12.25f;
		camera.Position.z = -102.04f;
	}

	//Personaje
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		posY++;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		posY--;
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		posZ++;
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		posZ--;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		posX--;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		posX++;


	// Reproducir Personaje animación
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		if (play == false && (FrameIndex > 1)) {
			resetElements();
			// Primera interpolación
			interpolationP();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else {
			play = false;
		}
	}

	// Reproducir Ovni animación
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		if (playO == false && (FrameIndexO > 1)) {
			resetElementsO();
			// Primera interpolación
			interpolationO();

			playO = true;
			playIndexO = 0;
			i_curr_steps_ovni = 0;
		}
		else {
			playO = false;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		animateLetrero = true;
	}
	//To Save a Frame
	/*if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		if (FrameIndex < MAX_P_FRAMES)
			saveFrame();
	}
*/
	//carga animaciones
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
		loadAnimationPer();
	if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
		loadAnimationOvni();
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height){
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos){
	if (firstMouse){
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
	camera.ProcessMouseScroll(yoffset);
}