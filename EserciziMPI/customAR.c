/*
1-Relying only on point-to-point MPI calls, implement a function with the same
signature/arguments and behaviour of MPI_Allreduce (call it «MPI_Allreduce_custom»).

2-Then, measure the its runtime, and compare it with the runtime of MPI_Allreduce.

3-Check if the runtime changes when using Send/Recv compared to Isend/Irecv/Wait

4-Think about how many bytes are you sending and how many send/recv are you executing
(similar to what we have done in the class for the broadcast). 
    Can you find a way to do it transmitting only 2*n bytes, and receiving only 2*n bytes (where n is the number of bytes in
the vector to reduce), and performing at most 2*log2(p) send and 2*log2(p) recvs (where p is
the number of processes)?
*/