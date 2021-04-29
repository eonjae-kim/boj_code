#define lli long long int
#define rint register int
#define MAXN 1001
#include<stdio.h>
struct Node {
	long long int x, y;
}body[MAXN + 10];
int alloc;
int L, N, dir, die;
lli survive_time;
int dx[4] = { 1, 0, -1, 0 }, dy[4] = { 0, -1, 0, 1 };
lli abs(lli x)
{
	return x > 0 ? x : -x;
}
lli min(lli a, lli b)
{
	return a > b ? b : a;
}
lli max(lli a, lli b)
{
	return a > b ? a : b;
}
int checkRange(lli i)
{
	if (body[i].x > L || body[i].y > L) return 1;
	else if (body[i].x < -L || body[i].y < -L) return -1;
	return 0;
}
int between(lli a, lli b, lli c)
{ /* a ¿Í b »çÀÌ¿¡ c */
	if (a <= b) {
		if (a <= c && c <= b) return 1;
	}
	else if (b <= a) {
		if (b <= c && c <= a) return 1;
	}
	return 0;
}
int eq(lli a, lli b, lli c)
{
	if (a == b && b == c && c == a) return 1;
	return 0;
}
lli checkBody(int st, int ed)
{
	if (body[st].x == body[ed].x){
		if (between(body[st].y, body[ed].y, body[alloc].y) && between(body[alloc].x, body[alloc - 1].x, body[st].x)) {
			return abs(body[st].x - body[alloc - 1].x);
		}
		if (eq(body[alloc].x, body[alloc - 1].x, body[st].x) && body[alloc - 1].y < body[alloc].y && between(body[alloc].y, body[alloc - 1].y, min(body[st].y, body[ed].y))) {
			return abs(body[alloc - 1].y - min(body[st].y, body[ed].y));
		}
		if (eq(body[alloc].x, body[alloc - 1].x, body[st].x) && body[alloc - 1].y > body[alloc].y && between(body[alloc].y, body[alloc - 1].y, max(body[st].y, body[ed].y))) {
			return abs(body[alloc - 1].y - max(body[st].y, body[ed].y));
		}
	}
	else if (body[st].y == body[ed].y) { 
		if (between(body[st].x, body[ed].x, body[alloc].x) && between(body[alloc].y, body[alloc - 1].y, body[st].y)) {
			return abs(body[st].y - body[alloc - 1].y);
		}
		if (eq(body[alloc].y, body[alloc - 1].y, body[st].y) && body[alloc-1].x < body[alloc].x && between(body[alloc].x, body[alloc - 1].x, min(body[st].x, body[ed].x))) {
			return abs(body[alloc - 1].x - min(body[st].x, body[ed].x));
		}
		if (eq(body[alloc].y, body[alloc - 1].y, body[st].y) && body[alloc - 1].x > body[alloc].x && between(body[alloc].x, body[alloc - 1].x, max(body[st].x, body[ed].x))) {
			return abs(body[alloc - 1].x - max(body[st].x, body[ed].x));
		}
	}
	return 0;
}

void run(int time, char direction)
{
	alloc++;
	body[alloc].x = body[alloc -1].x + (lli)dx[dir] * (lli)time;
	body[alloc].y = body[alloc-1].y + (lli)dy[dir] * (lli)time;

	if (alloc >= 4) {
		lli nearest = 2 * (lli)L + 2;
		for (rint i = 0; i < alloc - 3; i++) {
			lli chkbody = checkBody(i, i + 1);
			if (chkbody) {
				nearest = nearest > chkbody ? chkbody : nearest;
			}
		}
		if (nearest != 2 * (lli)L + 2) {
			survive_time += nearest;
			die = 1;
			return;
		}
	}
	rint chk = checkRange(alloc);
	if (abs(chk)) {
		if (dir == 0) {
			survive_time += abs(L + 1 - body[alloc - 1].x);
		}
		else if (dir == 1) {
			survive_time += abs(-L - 1 - body[alloc - 1].y);
		}
		else if (dir == 2) {
			survive_time += abs(-L - 1 - body[alloc - 1].x);
		}
		else {
			survive_time += abs(L + 1 - body[alloc - 1].y);
		}
		die = 1;
		return;
	}
	survive_time += abs(body[alloc].x - body[alloc - 1].x) + abs(body[alloc].y - body[alloc - 1].y);

	if (direction == 'L') {
		dir--;
		if (dir == -1) dir = 3;
	}
	else {
		dir++;
		if (dir == 4) dir = 0;
	}
}
int main() {
	int time;
	char direction = 'L';

	/* init */
	body[0].x = 0;
	body[0].y = 0;
	dir = 0;
	die = 0;

	scanf("%d", &L);
	scanf("%d", &N);

	for (rint i = 0; i < N; i++) {
		scanf("%d %c", &time, &direction);
		if (die) continue; // ¹ì »ç¸Á
		run(time, direction);
	}
	if (!die) {
		run(2 * (lli)L + 1, direction);
	}
	printf("%lld", survive_time);
	return 0;
}