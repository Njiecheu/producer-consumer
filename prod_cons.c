#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>

#define MaxItems 5
#define BufferSize 5

sem_t empty;
sem_t full;
int in = 0, out = 0;
int buffer[BufferSize];
pthread_mutex_t mutex;

void producteur(void *pno)
{
    int item;
    for (int i = 0; i < MaxItems; i++)
    {
        item = rand(); // produit des items aleatoire
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("le producteur %d: a insere l'item %d a %d\n",*((int *)pno), buffer[in],in);
        in = (in+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);

    }
    
    
}

void consommateur(void *cno)
{
    for (int i = 0; i < MaxItems; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        printf("le consommateur %d: a enleve l'item %d de %d\n",*((int *)cno), item,out);
        out = (out+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main()
{
    pthread_t pro[5], cons[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,BufferSize);
    sem_init(&full,0,0);

    int t[5] = {1,2,3,4,5}; // utilise pour numeroter le producteur et le consommateur

    for (int i = 0; i < 5; i++)
    {
        pthread_create(&pro[i],NULL,(void *)producteur, (void *)&t[i]);
        //pthread_create(&cons[i],NULL,(void *)consommateur, (void *)&t[i]);

        for(int i = 0; i < 5; i++)
        {
            pthread_join(pro[i],NULL);
        }

        for(int i = 0; i < 5; i++)
        {
            pthread_join(cons[i],NULL);
        }
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
    
}