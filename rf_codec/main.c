#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "hamming_codec.h"
#include "ccitt_whitening.h"
#include "rs_codec.h"

int main(int argc, const char * argv[]) {
    /*
    int n = 4;
    int size = 3;
    uint8_t data[] = { 0b10001000, 0b01000100, 0b11001100 };
    uint8_t encoded[size * 4];
    memset(encoded, 0, sizeof(encoded));
    
    uint16_t encoded_length = hamming_encode(data, size, n, encoded);
    
    uint8_t data_decoded[3];
    memset(data_decoded, 0, sizeof(data_decoded));
    hamming_decode(encoded, encoded_length, n, data_decoded);
    */
    
    uint16_t msg_in_len = 16;
    uint8_t msg_in[] = {0x40, 0xd2, 0x75, 0x47, 0x76, 0x17, 0x32, 0x06, 0x27, 0x26, 0x96, 0xc6, 0xc6, 0x96, 0x70, 0xec};
    
    uint8_t nsym = 10;
    uint16_t msg_out_len = nsym + msg_in_len;
    uint8_t msg_out[msg_out_len];
    memset(msg_out, 0, sizeof(msg_out));
    
    rs_init();
    rs_encode(nsym, msg_in, msg_in_len, msg_out, &msg_out_len);
    
    printf("msg_out encoded:\n");
    utils_print_array_8(msg_out, msg_out_len);
    
    msg_out[1] = 44;
    msg_out[2] = 55;
    msg_out[3] = 66;
    
    printf("msg_out corrupted:\n");
    utils_print_array_8(msg_out, msg_out_len);
    
    /*
     uint8_t synd_len = nsym + 1;
     uint8_t synd[synd_len];
     memset(synd, 0, sizeof(synd));
     
     rs_calc_syndromes(msg_out, msg_out_len, nsym, synd, &synd_len);
    
    printf("syndromes:\n");
    utils_print_array_8(synd, synd_len);
    
    bool is_corrupted = rs_message_is_corrupted(msg_out, msg_out_len, nsym);
    printf("message_is_corrupted: %d\n", is_corrupted);
    
    uint16_t err_loc_len = msg_out_len;
    uint8_t err_loc[err_loc_len];
    memset(err_loc, 0, sizeof(err_loc));
    rs_find_error_locator(nsym, synd, synd_len, err_loc, &err_loc_len);
    
    printf("error_locator:\n");
    utils_print_array_8(err_loc, err_loc_len);
    
    uint16_t err_pos_len = msg_out_len;
    uint8_t err_pos[err_loc_len];
    memset(err_pos, 0, sizeof(err_pos));
    rs_find_errors(err_loc, err_loc_len, msg_out_len, err_pos, &err_pos_len);
    
     printf("err_pos:\n");
     utils_print_array_8(err_pos, err_pos_len);
     */
     
    rs_correct_msg(msg_out, msg_out_len, 10);
    
    printf("msg_out corrected:\n");
    utils_print_array_8(msg_out, msg_out_len);
    
    return 0;
}
