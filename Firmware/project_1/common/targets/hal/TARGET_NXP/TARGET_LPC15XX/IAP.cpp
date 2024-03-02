#include <IAP.h>

uint8_t IAP::getPartID(){
	unsigned int command_param[5];
	unsigned int status_result[5];

	command_param[0] = COMMAND_PART_ID;

	iap_entry(command_param, status_result);

	if(status_result[0])
		return 0;

	return status_result[1] % 100;
}

bool IAP::getUniqueID(uint32_t (&data)[4]){
	unsigned int command_param[5];
	unsigned int status_result[5];

	command_param[0] = COMMAND_UID;

	iap_entry(command_param, status_result);

	if(status_result[0])
		return status_result[0];

	for(int i = 0; i < 4; i++){
		data[i] = status_result[i+1];
	}

	return false;
}
