extern int secCount;
extern int playSong;
void wdt_c_handler(){
  secCount++;
  switch(playSong){
  case 1:
    playSongOne();
    break;
  case 2:
    playSongTwo();
    break;
  case 3:
    playSongThree();
    break;
  default:
    playSong = 0;
  }
}
