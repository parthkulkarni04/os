#include <stdio.h>
void sort(int n, int AT[], int BT[], int P[]) {
int temp;
for (int i = 0; i < n - 1; i++) {
for (int j = 0; j < n - i - 1; j++) {
// Compare arrival times first
if (AT[j] > AT[j + 1]) {
// Swap arrival time
temp = AT[j];
AT[j] = AT[j + 1];
AT[j + 1] = temp;
// Swap burst time
temp = BT[j];
BT[j] = BT[j + 1];
BT[j + 1] = temp;
// Swap process IDs
temp = P[j];
P[j] = P[j + 1];
P[j + 1] = temp;
}
// If arrival times are the same, compare burst times
else if (AT[j] == AT[j + 1] && BT[j] > BT[j + 1]) {
// Swap burst time
temp = BT[j];
BT[j] = BT[j + 1];
BT[j + 1] = temp;
// Swap process IDs
temp = P[j];
P[j] = P[j + 1];

P[j + 1] = temp;
}
}
}
}
int main() {
int n;
printf("Enter the number of processes: ");
scanf("%d", &n);
int P[n], AT[n], BT[n], CT[n], TAT[n], WT[n], RT[n];
printf("Enter the arrival time and burst time of each process:\n");
for (int i = 0; i < n; i++) {
printf("Arrival time of P[%d]: ", i);
scanf("%d", &AT[i]);
}
for (int i = 0; i < n; i++) {
printf("Burst time of P[%d]: ", i);
scanf("%d", &BT[i]);
P[i] = i; // Initialize process IDs
}
// Sort processes based on arrival time and burst time (SJF)
sort(n, AT, BT, P);
int st = 0;
printf("The Gantt Chart is:\n");
printf("|");
int completed[n];
for (int i = 0; i < n; i++) {
completed[i] = 0;
}
while (1) {
int minBT = 9999; // Initialize with a large value
int minIndex = -1;
for (int i = 0; i < n; i++) {
if (AT[i] <= st && completed[i] == 0 && BT[i] < minBT) {
minBT = BT[i];
minIndex = i;
}
}

if (minIndex == -1) {
// No process available to execute, find the next process to

int minArrival = 9999;
for (int i = 0; i < n; i++) {
if (AT[i] > st && AT[i] < minArrival && completed[i] == 0) {
minArrival = AT[i];
}
}
if (minArrival == 9999) {
break; // All processes are completed
} else {
st = minArrival;
}
} else {
CT[minIndex] = st + BT[minIndex];
st = CT[minIndex];
completed[minIndex] = 1;
printf(" P%d |", P[minIndex]);
}
}
printf("\n");
// Calculate turnaround time, waiting time, and response time
for (int i = 0; i < n; i++) {
TAT[i] = CT[i] - AT[i];
WT[i] = TAT[i] - BT[i];
RT[i] = WT[i];
}

// Display the final table
printf("\n------------------------------------------------------------------------------------------------------------------ \n");
printf("| Process | Arrival Time | Burst Time | Completion Time |Turnaround Time | Waiting Time | Response Time |\n ");
printf("-----------------------------------------------------------------------------------------------------------------\n");
for (int i = 0; i < n; i++) {
printf("| P%d | %d | %d | %d| %d | %d | %d |\n", P[i], AT[i],BT[i], CT[i], TAT[i], RT[i], WT[i]):}
printf("------------------------------------------------------------------------------------------------------------------\n");
float avg = 0.0;

for (int i = 0; i < n; i++)
{
avg += (float)TAT[i] / n;
}
printf("\n\nAverage TAT: %.2f", avg);
float a = 0.0;
for (int i = 0; i < n; i++)
{
a += (float)WT[i] / n;
}
printf("\nAverage WT: %.2f", a);
float b = 0.0;
for (int i = 0; i < n; i++)
{
b += (float)RT[i] / n;
}
printf("\nAverage RT: %.2f\n", b);
return 0;
}