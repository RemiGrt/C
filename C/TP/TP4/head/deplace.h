#ifndef _deplace_
#define _deplace_
// donne les coordonne de la case voisine de la case depart
// en fonction de direction
// 0, 1, 2 ,3 = nord, est, sud, ouest
int deplace(int departX, int departY, \
            int *voisineX, int *voisineY, int direction);
#endif
