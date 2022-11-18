/**
 * @file temt6000_error_codes.h
 * @author Damian Ślusarczyk
 * @brief Contains error codes as an enumeration.
 * 
 * They describe the status of performed operations with TEMT6000.
 */
#ifndef TEMT6000_ERROR_CODES_H
#define TEMT6000_ERROR_CODES_H

typedef enum TEMT6000_error_t    TEMT6000_error_t;

/**
 * @brief Describes the status of performed operation with TEMT6000.
 * 
 */
enum TEMT6000_error_t
{
    TEMT6000_OK = 0,             /**< No error occurred - everything went fine */
    TEMT6000_INV_ARG,            /**< An invalid argument has been passed into the function */
    TEMT6000_ADC_CONF_FAIL,      /**< ADC configuration has failed */
    TEMT6000_ADC_OP_FAIL,        /**< ADC measurement has failed */
};

#endif /* TEMT6000_ERROR_CODES_H */
