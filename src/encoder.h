#ifndef encoder_h
#define encoder_h

void encoder_setup();
int get_leftcount();
int get_rightcount();
int get_target_count(int distance);
void reset_encoder();

#endif
