/*
 * reset.h
 *
 *  Created on: Jun 4, 2022
 *      Author: Jonathan
 */

#ifndef COMMON_API_RESET_H_
#define COMMON_API_RESET_H_

namespace Reset {

	bool watchdogCausedReset();
	bool externalCausedReset();
	bool brownOutCausedReset();
	bool softwareCausedReset();

}

#endif /* API_RESET_H_ */
