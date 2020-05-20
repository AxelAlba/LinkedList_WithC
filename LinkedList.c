/*
	Dynamic Memory Management and Data Type
	Developer:
	Axel T. Alba
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Set
{
	int data; //only specify dataStruct if multiple data is needed.
	struct Set *pNext; // pointer to the next node.
}Set; 

/*
	Description: This function creates and returns an empty Set.	
	Parameters: N.A.
	Precondition: N.A.	
*/
Set *create()
{
	return NULL;
}

/*
	Description: This function creates and returns a new node using a data.
	Parameters: data - an integer value used for node creation.
	Precondition: N.A.	
*/
Set *createNewNode(int data) 
{
	Set *pTemp;

	if((pTemp = malloc(sizeof(Set))) == NULL)
	{
		printf("ERROR: NOT ENOUGH MEMORY.\n");
		return NULL;
	}
	pTemp-> data = data;
	pTemp -> pNext = NULL;

	return pTemp;

}

/*
	Description: This function displays on screen the elements of the ordered Set.
	Parameters: *pFirst - pointer to the head of the Set.
	Precondition: The Set should have been created/initialized(using the create() function) first.	
*/
void print(Set *pFirst) 
{
	printf("(");
	while (pFirst != NULL)
	{
		if (pFirst -> pNext == NULL)
			printf("%d", pFirst -> data);
		else
			printf("%d, ", pFirst -> data);
		pFirst = pFirst -> pNext;
	}
	printf(")\n");
}

/*
	Description: This function free up the memory allocated for the ordered Set.
	Parameters: *pFirst - pointer to the head of the Set.
	Precondition: The Set should not be empty.	
*/
void freeList(Set *pFirst)
{
	Set *pCurrent;
	pCurrent = pFirst;
	while (pFirst != NULL)
	{
		pFirst = pFirst -> pNext;
		free(pCurrent);
		pCurrent = pFirst;
	}
}

/*
	Description: This function converts a data into a node and adds it into the specified Set. It then returns the pointer to the head of the ordered Set.
	Parameters: *pFirst - pointer to the head of the Set.
				data -  an integer value used for node creation.
	Precondition: The Set should have been created/initialized(using the create() function) first.	
*/
Set *add(Set *pFirst, int data)
{
	int newKey;
	Set *pTemp, *pTrail, *pCurrent;

	pTemp = createNewNode(data);

	if (pFirst == NULL)
		pFirst = pTemp;
	else
	{
		newKey = data;
		pTrail = NULL;
		pCurrent = pFirst;

		while (pCurrent != NULL)
		{
			if (newKey < pCurrent -> data)
				break;
			else
			{
				pTrail = pCurrent;
				pCurrent = pCurrent->pNext;
			}
		}

		pTemp -> pNext = pCurrent;

		if(pTrail != NULL)
			pTrail -> pNext = pTemp;
		else
			pFirst = pTemp;
	}
	return pFirst;
}

/*
	Description: This function deletes a node in the Set using the specified Key. It then returns the pointer to the head of the Set.
	Parameters: *pFirst - pointer to the head of the ordered Set.
				key -  an integer value used for comparison with the datas of the set.
	Precondition: The Set should exist(using the create() function) first.	
*/
Set *delete(Set *pFirst, int key)
{
	int found;
	Set *pTrail;
	Set *pCurrent;

	if (pFirst == NULL)
		printf("Empty list , no node to delete.\n");
	else 
	{
		pTrail = NULL;
		pCurrent = pFirst;
		while (pCurrent != NULL && !found) 
		{
			if (key == pCurrent->data)
			found = 1; 
			else if (key > pCurrent->data) 
			{
				pTrail = pCurrent;
				pCurrent = pCurrent->pNext;
			}
			else
				break;
		}
		if (found) 
		{
			if (pTrail == NULL)
				pFirst = pFirst ->pNext;
			else
				pTrail ->pNext = pCurrent->pNext;
			free(pCurrent);
		}
		else
			printf("key %d is not in the list.\n");
	}
	return pFirst;
}

/*
	Description: This function returns a new ordered Set containing the common elements of the two specified sets.
	Parameters: *s1 - pointer to the head of the Set 1.
				*s2 -  pointer to the head of the Set 2.
	Precondition: Both Sets should exist first (using the create() function).	
*/
Set *intersect(Set *s1, Set *s2)
{
	Set *s3, *p1, *p2;
	s3 = create();

	p1 = s1;
	p2 = s2;
	while (p1 != NULL && p2 != NULL)
	{
		if (p1 -> data < p2 -> data)
			p1 = p1 ->pNext;
		else if (p2 -> data < p1 -> data)
			p2 = p2 -> pNext;
		else
		{
			s3 = add(s3, p2 -> data);
			p1 = p1 ->pNext;
			p2 = p2 -> pNext;
		}
	}
	return s3;
}


/*
	Description: This function returns a new ordered Set created by merging the elements of the two specified sets.
	Parameters: *s1 - pointer to the head of the Set 1.
				*s2 -  pointer to the head of the Set 2.
	Precondition: Both Sets should exist first (using the create() function).	
*/
Set *combine(Set *s1, Set *s2)
{
	Set *s3, *sct, *p1, *p2;
	s3 = create();
	sct = intersect(s1, s2);
	p1 = s1;
	p2 = s2;

	while (p1 != NULL)
	{
		s3 = add(s3, p1 -> data);
		p1 = p1->pNext;
	}

	while (p2 != NULL)
	{
		s3 = add(s3, p2 -> data);
		p2 = p2->pNext;
	}

	while (sct != NULL)
	{
		s3 = delete(s3, sct -> data);
		sct = sct -> pNext;
	}

	freeList(sct);
	return s3;
}

/*
	Description: This function returns a new ordered Set containing the unique elements of the first Set, that are not found in the second Set.
	Parameters: *s1 - pointer to the head of the Set 1.
				*s2 -  pointer to the head of the Set 2.
	Precondition: Both Sets should exist first (using the create() function).	
*/
Set *difference(Set *s1, Set *s2)
{
	Set *s3, *p1, *p2;
	int flag;
	s3 = create();

	p1 = s1;
	p2 = s2;
	while (p1 != NULL)
	{
		p2 = s2;
		flag = 0;
		while (p2 != NULL)
		{
			if (p1->data == p2->data)
			{
				flag = 1;
				break;
			}
			p2 = p2 -> pNext;
		}
		if (flag == 0)
			s3 = add(s3, p1 -> data);

		p1 = p1 ->pNext;
	}
	return s3;
}

//for testing the functions above.
int main()
{
	Set *s1, *s2, *s3, *s4;
	s1 = create();
	s2 = create();
	s3 = create();
	s4 = create();
	s1 =add (s1, 4);
	s1 =add (s1, 2);
	s1 =add (s1, 8);
	s1 =add (s1, 6);
	print (s1);					// this statement will display (2, 4, 6, 8)
	s2 =add (s2, 2);
	s2 =add (s2, 5);
	print (s2);       			// this statement will display (2, 5)
	s3 =add (s3, 7);
	s3=add (s3, 6);
	print (s3);     			// this statement will display (6, 7)
	print(combine(s1,s2)); 		// this statement will return (2, 4, 5, 6, 8)
	print (intersect(s1, s2)); 	// this statement will return (2)
	print (difference(s1, s3));	// this statement will return (2, 4, 8)
	print (intersect(s2, s3));	// this statement will return ()
	return 0;
}

