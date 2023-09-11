/*Darren  Buck PJX598*/

#define Max_firstName_LEN 32
#define Max_lastName_LEN 32
#define Max_streetName_LEN 64
#define Max_cityName_LEN 64
#define Max_stateAbbr_LEN 2
#define Max_ICDcode_LEN 10
#define Max_NumOfICDcodesandDates_LEN 4
#define Max_Buff_LEN 1024
#define Max_phoneType_LEN 4
/*--------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
/*--------------------------------------------------*/
enum State {
	NONE, AL, AK, AZ, AR, CA, CO, CT, DC, DE, FL, GA, HI, ID, IL, IN, IA, KS, KY, LA, ME, MD, MA,
	MI, MN, MS, MO, MT, NE, NV, NH, NJ, NM, NY, NC, ND, OH, OK, OR, PA, RI, SC, SD, TN, TX, UT, VT, VA, WA, WV, WI, WY
};
enum Phone { NO_ENTERY, WORK, CELL, HOME };
/*--------------------------------------------------*/
char buffer[Max_Buff_LEN];
char* lastName = NULL;
char* firstName = NULL;
unsigned short streetNum;
char* streetName = NULL;
char* cityName = NULL;
enum State stateEnum;
char* state = NULL;
unsigned short plusFour;
unsigned int zip;
char* phoneType = NULL;
int i;
unsigned int FileINDX;
FILE* Fptr = NULL;
FILE* FptrIDX = NULL;
/*--------------------------------------------------*/
typedef struct Phone_struct {
	unsigned short areaC;
	unsigned int phoneNum;
	enum Phone type;
} phone;
/*--------------------------------------------------*/
 typedef struct ICD_struct{
	char* ICDcode;
	unsigned int ICDdate;
} icd;

phone phoneInfo = {
	 .areaC = 0,
	 .phoneNum = 0,
	 .type = 0,
};
icd* ICDinfo;
typedef struct Command_Peram {
	size_t stringlength;
	char* string;
	unsigned int numCodes;

	
} Prompt;
Prompt cmd;
/*--------------------------------------------------*/
/*--------------------------------------------------*/
void GetFileName(void) {
	sprintf(buffer, "%s_%s_%d.icd", lastName, firstName, FileINDX);
}
void clearBuffer(char* buffer)
{
	memset(buffer, '\0', Max_Buff_LEN);
}
int getValidString(size_t stringMax, char* buffer) {
	int valid = 1;
	/*fgets(buffer, Max_Buff_LEN, stdin);*/
	scanf("%[^\n]%*c",buffer);
	if ((strlen(buffer) <= 0) || (strlen(buffer) > stringMax)) {
		printf("Error incorect entry. Entery must be between 0 and %zu\n", stringMax);
		clearBuffer(buffer);
		valid = 0;
	}
	return valid;
}
void patientFirstName(void) {
	int valid = 0;
	do {
		printf("Please enter your first name.\n");
		valid = getValidString(Max_firstName_LEN, buffer);

	} while (valid == 0);
	i=0;
	for(i=0;i<strlen(buffer);i++)
	{buffer[i] = toupper(buffer[i]);}
	i=0;
	firstName = (char*)malloc((strlen(buffer)) * sizeof(char));
	strcpy(firstName, buffer);
	clearBuffer(buffer);
}
void patientLastName(void) {
	int valid = 0;
	do {
		printf("Please enter your last name.\n");
		valid = getValidString(Max_lastName_LEN, buffer);

	} while (valid == 0);
	i=0;
	for(i=0;i<strlen(buffer);i++)
	{buffer[i] = toupper(buffer[i]);}
	i=0;
	lastName = (char*)malloc((strlen(buffer)) * sizeof(char));
	strcpy(lastName, buffer);
	clearBuffer(buffer);
}
void StreetNumber(void) {
	do {
		printf("Please enter your street number.\n");
		scanf("%hu", &streetNum);
		getchar();
		if (streetNum > 0 && streetNum < 60000) {
			break;
		}
		else {
			printf("Error incorect entry. Please try again.\n");
		}
	} while (!(streetNum > 0) && !(streetNum < 60000));

}
void StreetName(void) {
	int valid = 0;
	do {
		printf("Please enter the name of your street.\n");
	valid =	getValidString(Max_streetName_LEN, buffer);

	} while (valid == 0);
	i=0;
	for(i=0;i<strlen(buffer);i++)
	{buffer[i] = toupper(buffer[i]);}
	i=0;
	streetName = (char*)malloc((strlen(buffer)) * sizeof(char));
	strcpy(streetName, buffer);
	clearBuffer(buffer);
}
void patientCity(void) {
	int valid = 0;
	do {
		printf("Please enter the name of your city.\n");
	valid =	getValidString(Max_cityName_LEN, buffer);

	} while (valid == 0);
	i=0;
	for(i=0;i<strlen(buffer);i++)
	{buffer[i] = toupper(buffer[i]);}
	i=0;
	cityName = (char*)malloc((strlen(buffer)) * sizeof(char));
	strcpy(cityName, buffer);
	clearBuffer(buffer);
}
enum State patientState(void) {
	bool validState = false;
	int valid = 0;
	do {
		printf("Please enter the abbriviation of your state.\n");
	valid =	getValidString(Max_stateAbbr_LEN+1, buffer);

	} while (valid == 0);
	state = (char*)malloc((strlen(buffer)) * sizeof(char));
	strcpy(state, buffer);
	clearBuffer(buffer);

	for (i = 0; i < 2; i++) {
		state[i] = toupper(state[i]);
	}
	do {
		switch (state[0])
		{
		case 'A':
			switch (state[1])
			{
			case 'K': stateEnum = AK; validState = true;
				break;
			case 'L': stateEnum = AL; validState = true;
				break;
			case 'R': stateEnum = AR; validState = true;
				break;
			case 'Z': stateEnum = AZ; validState = true;
				break;
			default: stateEnum = NONE; validState = false;
			}; break;
		case 'C':
			switch (state[1])
			{
			case 'A': stateEnum = CA; validState = true;
				break;
			case 'O': stateEnum = CO; validState = true;
				break;
			case 'T': stateEnum = CT; validState = true;
				break;
			default: stateEnum = NONE; validState = false;
			}; break;
		case 'D':
			switch (state[1])
			{
			case 'E': stateEnum = DE; validState = true;
				break;
			case 'C': stateEnum = DC; validState = true;
				break;
			default: stateEnum = NONE; validState = false;
			}; break;
		case 'F':
			switch (state[1])
			{
			case 'L': stateEnum = FL; validState = true;
				break;
			default: stateEnum = NONE; validState = false;
			}; break;
		case 'G':
			switch (state[1])
			{
			case 'A': stateEnum = GA; validState = true;
				break;
			default: stateEnum = NONE; validState = false;
			}; break;
		case 'H':
			switch (state[1])
			{
			case 'I': stateEnum = HI; validState = true;
				break;
			default: stateEnum = NONE; validState = false;
			}; break;
		case 'I':
			switch (state[1])
			{
			case 'D': stateEnum = ID; validState = true;
				break;
			case 'L': stateEnum = IL; validState = true;
				break;
			case 'N': stateEnum = IN; validState = true;
				break;
			case 'A': stateEnum = IA; validState = true;
				break;
			default: stateEnum = NONE; validState = false;
			}; break;
		case 'K':
			switch (state[1])
			{
			case 'S': stateEnum = KS; validState = true;
				break;
			case 'Y': stateEnum = KY; validState = true;
				break;
			default: stateEnum = NONE; validState = false;
			}; break;
		case 'L':
			switch (state[1])
			{
			case 'A': stateEnum = LA; validState = true;
				break;
			default: stateEnum = NONE; validState = false;
			}; break;
		case 'M':
			switch (state[1])
			{
			case 'E': stateEnum = ME; validState = true;
				break;
			case 'D': stateEnum = MD; validState = true;
				break;
			case 'A': stateEnum = MA; validState = true;
				break;
			case 'I': stateEnum = MI; validState = true;
				break;
			case 'N': stateEnum = MN; validState = true;
				break;
			case 'S': stateEnum = MS; validState = true;
				break;
			case 'O': stateEnum = MO; validState = true;
				break;
			case 'T': stateEnum = MT; validState = true;
				break;
			default: stateEnum = NONE; validState = false;
			}; break;
		case 'N':
			switch (state[1])
			{
			case 'E': stateEnum = NE; validState = true;
				break;
			case 'V': stateEnum = NV; validState = true;
				break;
			case 'H': stateEnum = NH; validState = true;
				break;
			case 'J': stateEnum = NJ; validState = true;
				break;
			case 'M': stateEnum = NM; validState = true;
				break;
			case 'Y': stateEnum = NY; validState = true;
				break;
			case 'C': stateEnum = NC; validState = true;
				break;
			case 'D': stateEnum = ND; validState = true;
				break;
			default: stateEnum = NONE; validState = false;
			}; break;
		case 'O':
			switch (state[1])
			{
			case 'H': stateEnum = OH; validState = true;
				break;
			case 'K': stateEnum = OK; validState = true;
				break;
			case 'R': stateEnum = OR; validState = true;
				break;
			default: stateEnum = NONE; validState = false;
			}; break;
		case 'P':
			switch (state[1])
			{
			case 'A': stateEnum = PA; validState = true;
				break;
			default: stateEnum = NONE; validState = false;
			}; break;
		case 'S':
			switch (state[1])
			{
			case 'C': stateEnum = SC; validState = true;
				break;
			case 'D': stateEnum = SD; validState = true;
				break;
			default: stateEnum = NONE; validState = false;
			}; break;
		case 'T':
			switch (state[1])
			{
			case 'N': stateEnum = TN; validState = true;
				break;
			case 'X': stateEnum = TX; validState = true;
				break;
			default: stateEnum = NONE; validState = false;
			}; break;
		case 'U':
			switch (state[1])
			{
			case 'T': stateEnum = UT; validState = true;
				break;
			default: stateEnum = NONE; validState = false;
			}; break;
		case 'V':
			switch (state[1])
			{
			case 'T': stateEnum = VT; validState = true;
				break;
			case 'A': stateEnum = VA; validState = true;
				break;
			default: stateEnum = NONE; validState = false;
			}; break;
		case 'W':
			switch (state[1])
			{
			case 'A': stateEnum = WA; validState = true;
				break;
			case 'V': stateEnum = WV; validState = true;
				break;
			case 'I': stateEnum = WI; validState = true;
				break;
			case 'Y': stateEnum = WY; validState = true;
				break;
			default: stateEnum = NONE; validState = false;
			}; break;
		}
		if (validState == false) {
			printf("Error. Please re-enter a valid state abbreviation.");
		}
	} while (validState == false);
	return stateEnum;
}
void printStateEnum(enum State stateEnum) {
	switch (stateEnum)
	{
	case AL: printf("AL");
		break;
	case AK: printf("AK");
		break;
	case AZ: printf("AZ");
		break;
	case AR: printf("AR");
		break;
	case CA: printf("CA");
		break;
	case CO: printf("CO");
		break;
	case CT: printf("CT");
		break;
	case DC: printf("DC");
		break;
	case DE: printf("AK");
		break;
	case FL: printf("FL");
		break;
	case GA: printf("GA");
		break;
	case HI: printf("HI");
		break;
	case ID: printf("ID");
		break;
	case IL: printf("IL");
		break;
	case IN: printf("IN");
		break;
	case IA: printf("IA");
		break;
	case KS: printf("KS");
		break;
	case KY: printf("KY");
		break;
	case LA: printf("LA");
		break;
	case ME: printf("ME");
		break;
	case MD: printf("MD");
		break;
	case MA: printf("MA");
		break;
	case MI: printf("MI");
		break;
	case MN: printf("MN");
		break;
	case MS: printf("MS");
		break;
	case MO: printf("MO");
		break;
	case MT: printf("MT");
		break;
	case NE: printf("NE");
		break;
	case NV: printf("NV");
		break;
	case NH: printf("NH");
		break;
	case NJ: printf("NJ");
		break;
	case NM: printf("NM");
		break;
	case NY: printf("NY");
		break;
	case NC: printf("NC");
		break;
	case ND: printf("ND");
		break;
	case OH: printf("OH");
		break;
	case OK: printf("OK");
		break;
	case OR: printf("OR");
		break;
	case PA: printf("PA");
		break;
	case RI: printf("RI");
		break;
	case SC: printf("SC");
		break;
	case SD: printf("SD");
		break;
	case TN: printf("TN");
		break;
	case TX: printf("TX");
		break;
	case UT: printf("UT");
		break;
	case VT: printf("VT");
		break;
	case VA: printf("VA");
		break;
	case WA: printf("WA");
		break;
	case WV: printf("WV");
		break;
	case WI: printf("WI");
		break;
	case WY: printf("WY");
		break;
	default:  printf("Error");
		break;

	}
}
void four_Zip(void) {

	do {
		printf("Please enter the first 4 of your zip code.\n");
		scanf("%hu", &plusFour);
		getchar();
		if (plusFour > 1000 && plusFour < 9999) {
			break;
		}
		else {
			printf("Error incorect entry. Please try again.\n");
		}
	} while (!(plusFour > 1000) && !(plusFour < 9999));
}
void patientZip(void) {
	unsigned long longzip;
	do {
		printf("Please enter your zip code.\n");
		scanf("%lu", &longzip);
		getchar();
		if (longzip > 1000 && longzip < 99950) {
			zip = (unsigned int)longzip;
		}
		else {
			printf("Error incorect entry. Please try again.\n");
		}
	} while (!(longzip > 1000) && !(longzip < 99950));
}
void areaCode(void) {
	do {
		printf("Please enter the area code for your phone number.\n");
		scanf("%hu", &phoneInfo.areaC);
		getchar();
		if (phoneInfo.areaC > 200 && phoneInfo.areaC < 999) {
			break;
		}
		else {
			printf("Error incorect entry. Please try again.\n");
		}
	} while (!(phoneInfo.areaC > 200) && !(phoneInfo.areaC < 999));

}
void patientPhoneNumber(void) {
	do {
		printf("Please enter your phone number without the area code.\n");
		scanf("%u", &phoneInfo.phoneNum);
		getchar();
		if (phoneInfo.phoneNum > 2010000 && phoneInfo.phoneNum < 9999999) {
			break;
		}
		else {
			printf("Error incorect entry. Please try again.\n");
		}
	} while (!(phoneInfo.phoneNum > 2010000) && !(phoneInfo.phoneNum < 9999999));
}
void PhoneType(void) {
	bool check = false;
	int valid = 0;
	do {
		printf("Please enter your prefered phone type as WORK, CELL, or HOME.\n");
		valid = getValidString(Max_phoneType_LEN+1, buffer);

	} while (valid == 0);
	phoneType = (char*)malloc((strlen(buffer)) * sizeof(char));
	strcpy(phoneType, buffer);
	clearBuffer(buffer);


	do {
		switch (phoneType[0])
		{
		case 'C':
		case 'c':
			phoneInfo.type = CELL; check = true;
			break;
		case 'W':
		case 'w':
			phoneInfo.type = WORK; check = true;
			break;
		case 'H':
		case 'h': phoneInfo.type = HOME; check = true;
			break;
		default: phoneInfo.type = NO_ENTERY; check = false;
			break;
		}
	} while (check == false);
}
void phoneTypePrint(void) {
	if (phoneInfo.type == CELL) {
		printf("Cell phone\n\n");
	}
	else if (phoneInfo.type == HOME) {
		printf("Home phone\n\n");
	}
	else if (phoneInfo.type == WORK) {
		printf("Work phone\n\n");
	}
}
void patientICDcode(int i) {
	int valid = 0;
	do {
		printf("Please enter Patient ICDinfo(%d) code.\n", i);
	valid = 	getValidString(Max_ICDcode_LEN, buffer);
	} while (valid == 0);
	ICDinfo[i].ICDcode = (char*)malloc((strlen(buffer)) * sizeof(char));
	strcpy(ICDinfo[i].ICDcode, buffer);
	clearBuffer(buffer);
}
void ICDdateConverter(int i) {
	unsigned int date;
	int day;
	int month;
	int year;
	do {
		do {
			printf("Please enter the day(DD) of ICDinfo(%d) code.\n", i);
			scanf("%d", &day);
			getchar();
			if (day > 0 && day <= 31) {
				break;
			}
			else {
				printf("Error incorect entry. Please try again.\n");
			}
		} while (!(day > 0 && day <= 31));
		do {
			printf("Please enter the month(MM) of ICDinfo(%d) code.\n", i);
			scanf("%d", &month);
			getchar();
			if (month > 0 && month <= 12) {
				break;
			}
			else {
				printf("Error incorect entry. Please try again.\n");
			}
		} while (!(month > 0 && month < 31));
		do {
			printf("Please enter the year(YYYY) of ICDinfo(%d) code.\n", i);
			scanf("%d", &year);
			getchar();
			if (year > 2020 && year <= 2028) {
				break;
			}
			else {
				printf("Error incorect entry. Please try again.\n");
			}
		} while (!(year > 2020 && year < 2028));

		date = (day)+(month * 100) + (year * 10000);
		if (date > 19000101 && date < 99999999) {
			ICDinfo[i].ICDdate = date;
		}
		else {
			printf("Error incorect entry. Please try again.\n");
		}
	} while (!(date > 20200101) && !(date < 99999999));
}
void printCODEandDATE() {
	int day;
	int month;
	int year;
	i = 0;
	for (i = 0; i < cmd.numCodes; i++) {
		day = ICDinfo[i].ICDdate % 100;
		month = (ICDinfo[i].ICDdate / 100) % 100;
		year = ICDinfo[i].ICDdate / 10000;
		printf("ICDinfo(%d): %s Date: %d/%d/%d\n\n", i, ICDinfo[i].ICDcode, year, month, day);
	}

}
int codePerams(unsigned argc,char* argv[]){
	cmd.string = NULL;
	cmd.numCodes = Max_NumOfICDcodesandDates_LEN;
	cmd.stringlength = Max_Buff_LEN;
	if (argc > 3){
		return 4;
	}
	if (argc == 1){
return 1;
	}
	switch (argv[1][1]){
		case 'c':
			cmd.stringlength=strlen(argv[2]);
			cmd.string = (char*)malloc((cmd.stringlength) * sizeof(char));
			if(strcmp(argv[2],"-r")==0){
				return 4;
			}
			else{ 
			cmd.string = argv[2];
			cmd.numCodes = atoi(cmd.string); 
			return 1;
			}
		case 'r':
			cmd.stringlength=strlen(argv[2]);
			cmd.string = (char*)malloc((cmd.stringlength) * sizeof(char));
			if(strcmp(argv[2],"-c")==0){
				return 4;
			}
			else{
			cmd.string = argv[2];
			return 2;
			}
		case 'h':
			printf("Command options -c,-r,-h\n");
			printf("-c will allow you to choose the number of ICD codes to input.\n");
			printf("Format is Exicutable_-c_number\n");
			printf("-r will allow you to choose the number of ICD codes to input.\n");
			printf("Format is Exicutable_-r_fileName\n");
			printf("-h is the help bar and will print this again.\n");
			printf("You can only use one perameter at a time.\n");
			return 3;
	}
	return 4;
}
int main(int argc, char* argv[])
{
	bool valid;
	
	FptrIDX = fopen("ICDinfo.idx", "r");
	if (FptrIDX == NULL) {
		printf("Error ICDinfo.idx did not open\n");
    	FptrIDX = fopen("ICDinfo.idx", "w");
    	fprintf(FptrIDX,"0");
	}
	fscanf(FptrIDX, "%u", &FileINDX);
	fclose(FptrIDX);

	int paramReturn;
	paramReturn = codePerams(argc,argv);

	ICDinfo = (icd*)malloc(cmd.numCodes * sizeof(icd));
	i=0;
	for (i=0;i<cmd.numCodes;i++){
		ICDinfo[i].ICDcode = NULL;
		ICDinfo[i].ICDdate = 0;
	}
	
	if (paramReturn == 2){
			Fptr = fopen(cmd.string,"r");
			if (Fptr == NULL) {
				valid = false;
       			printf("Error patient record not found.\n");
				return 6;
				}
			else {
				fscanf(Fptr, "%[^\n]%*c", buffer);
				lastName = (char*)malloc((strlen(buffer)) * sizeof(char));
					strcpy(lastName, buffer);
					clearBuffer(buffer);
				fscanf(Fptr, "%[^\n]%*c", buffer);
				firstName = (char*)malloc((strlen(buffer)) * sizeof(char));
					strcpy(firstName, buffer);
					clearBuffer(buffer);
				fscanf(Fptr, "%hu%*c", &streetNum);
				fscanf(Fptr, "%[^\n]%*c", buffer);
				streetName = (char*)malloc((strlen(buffer)) * sizeof(char));
					strcpy(streetName, buffer);
					clearBuffer(buffer);
				fscanf(Fptr, "%[^\n]%*c", buffer);
					cityName = (char*)malloc((strlen(buffer)) * sizeof(char));
					strcpy(cityName, buffer);
					clearBuffer(buffer);
				fscanf(Fptr, "%u%*c", &stateEnum);
				fscanf(Fptr, "%hu%*c",&plusFour);
				fscanf(Fptr, "%u%*c", &zip);
				fscanf(Fptr, "%hu%*c", &phoneInfo.areaC);
				fscanf(Fptr, "%u%*c", &phoneInfo.phoneNum);
				fscanf(Fptr, "%u%*c", &phoneInfo.type);
				fscanf(Fptr,"%u%*c", &cmd.numCodes);
				i=0;
				for (i = 0; i < cmd.numCodes; i++) {
					fscanf(Fptr, "%[^\n]%*c", buffer);
					ICDinfo[i].ICDcode = (char*)malloc((strlen(buffer)) * sizeof(char));
					strcpy(ICDinfo[i].ICDcode, buffer);
					clearBuffer(buffer);
					fscanf(Fptr, "%u%*c", &ICDinfo[i].ICDdate);
				}
					printf("\n%s\n", lastName);
					printf("%s\n",firstName);
					printf("%hu %s\n", streetNum,streetName);
					printf("%s\n", cityName);
					printStateEnum(stateEnum);
					printf("\n%u-%u\n", plusFour, zip);
					printf("(%hu) %u\n", phoneInfo.areaC, phoneInfo.phoneNum);
					phoneTypePrint();
					printCODEandDATE();
				 	valid = true;
				 	fclose(Fptr);
					clearBuffer(buffer);
					free(firstName);
					free(lastName);
					free(firstName);
					free(lastName);
					free(streetName);
					free(cityName);
					i = 0;
					while (i < cmd.numCodes) {
						free(ICDinfo[i].ICDcode);
						++i;
					}
					free(ICDinfo);
				}
				return 7;
		}
if(paramReturn == 1 || paramReturn == 8){
				patientFirstName();
				patientLastName();
				StreetNumber();
				StreetName();
				patientCity();
				enum State stateEnum = patientState();
				four_Zip();
				patientZip();
				areaCode();
				patientPhoneNumber();
				PhoneType();
				i=0;
				for (i = 0; i < cmd.numCodes; i++) {
					patientICDcode(i);
					ICDdateConverter(i);
				}
					printf("\n%s, %s\n", lastName, firstName);
					printf("%hu %s\n", streetNum,streetName);
					printf("%s\n", cityName);
					printStateEnum(stateEnum);
					printf("\n%u-%u\n", plusFour, zip);
					printf("(%hu) %u\n", phoneInfo.areaC, phoneInfo.phoneNum);
					phoneTypePrint();
					printCODEandDATE();
	char wantToSave;	
	printf("Do you want to save this patients file?\n Press 'Y' for yes and 'N' for no.\n");
	scanf("%c", &wantToSave);
	getchar();
			if (wantToSave == 'y' || wantToSave == 'Y')
			{    
				++ FileINDX;
				FptrIDX = fopen("ICDinfo.idx","w");
				fprintf(FptrIDX,"%u",FileINDX);
				fclose(FptrIDX);
				
					GetFileName();
					Fptr = fopen(buffer, "w");

					if (Fptr == NULL) {
						printf("%s failed to open.\n\n", buffer);
						return 2;
					}
					printf("%s file is now open and will upload content.\n\n",buffer);
					fprintf(Fptr, "%s\n", lastName);
					fprintf(Fptr, "%s\n", firstName);
					fprintf(Fptr, "%hu\n", streetNum);
					fprintf(Fptr, "%s\n", streetName);
					fprintf(Fptr, "%s\n", cityName);
					fprintf(Fptr, "%u\n", stateEnum);
					fprintf(Fptr, "%u\n",plusFour);
					fprintf(Fptr, "%u\n", zip);
					fprintf(Fptr, "%hu\n",phoneInfo.areaC);
					fprintf(Fptr, "%u\n", phoneInfo.phoneNum);
					fprintf(Fptr, "%d\n", phoneInfo.type);
					fprintf(Fptr,"%u\n",cmd.numCodes);
						for (i = 0; i < cmd.numCodes; i++) {
							fprintf(Fptr, "%s\n", ICDinfo[i].ICDcode);
							fprintf(Fptr, "%u\n", ICDinfo[i].ICDdate);
						}
					fclose(Fptr);
					printf("Data successfully uploaded to file %s\n", buffer);
					printf("The file is now closed.\n");
					clearBuffer(buffer);
					free(firstName);
					free(lastName);
					free(streetName);
					free(cityName);
					i = 0;
					while (i < cmd.numCodes) {
					free(ICDinfo[i].ICDcode);
					++i;
					}
					free(ICDinfo);
					return 3;
				}
			}

					i = 0;
					while (i < cmd.numCodes) {
					free(ICDinfo[i].ICDcode);
					++i;
					}
					free(ICDinfo);
if (paramReturn == 4){
	printf("Entered peramaters are outside scope.");
	printf("Command options -c,-r,-h\n");
	printf("-c will allow you to choose the number of ICD codes to input.\n");
	printf("Format is Exicutable_-c_number\n");
	printf("-r will allow you to choose the number of ICD codes to input.\n");
	printf("Format is Exicutable_-r_fileName\n");
	printf("-h is the help bar and will print this again.\n");
	printf("You can only use one perameter at a time.\n");

}
	return 0;
}