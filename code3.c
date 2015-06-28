#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define N 80

struct bedplace
{
	char name[N];
	struct bedplace *next;
	struct bedplace *prev;
};
struct rooms
{

	int room;
	struct  bedplace *place;
	struct rooms *next;
};
struct hotel_floor
{
	int floor;
	struct rooms *floor_room;
	struct hotel_floor *next;
	struct hotel_floor *prev;
};

void clean_stdin(void)
{
	int c;
	do
	{
		c = getchar();
	} while (c != '\n' && c != EOF);
}

int scani()
{
	int c;
	do
	{
		scanf("%d", &c);
		clean_stdin();
		if (!c)
		{
			printf("Input error");
			continue;
		}
		else
			return c;
		break;
	} while (1);
}

char scanc()
{
	char c;
	do
	{
		scanf("%c", &c);
		clean_stdin();
		if (!c)
		{
			printf("Input error");
			continue;
		}
		else
			return c;
		break;
	} while (1);
}

int save_bed_place(struct bedplace *all_place,FILE *result_file)
{
	struct bedplace *temp = all_place;
	if(!all_place)
	{
		printf("Bed place isn't create!\n");
		return 0;
	}
	do
	{
		if(temp->name[0] == 0)
			fprintf(result_file,"\t\tPlace is free\n");
		else
			fprintf(result_file,"\t\tIn this room live %s",temp->name);
		temp = temp->next;
	} while(temp != all_place);
	return 0;
}

void save_rooms(struct rooms *room,FILE *result_file)
{
	struct rooms *temp = room;
	if(!room)
	{
		fprintf(result_file,"Room isn't create!\n");
		return;
	}
	do
	{
		fprintf(result_file,"\tCurrent room is %d\n",temp->room);
		save_bed_place(temp->place,result_file);
		temp = temp->next;
	} while(temp != NULL);
}

int save_floors(struct hotel_floor *floor,FILE *result_file)
{
	struct hotel_floor *temp = floor;
	if(!floor)
	{
		fprintf(result_file,"Hotel isn't create!\n");
		return 0;
	}
	do
	{
		fprintf(result_file,"Current floor is %d\n",temp->floor);
		save_rooms(temp->floor_room,result_file);
		temp = temp->next;
	} while(temp != floor);
	return 0;
}

int see_bed_place(struct bedplace *all_place)
{
	struct bedplace *temp = all_place;
	if(!all_place)
	{
		printf("Bed place isn't create!\n");
		return 0;
	}
	do
	{
		if(temp->name[0] == 0)
			printf("\t\tPlace is free\n");
		else
			printf("\t\tIn this room live %s",temp->name);
		temp = temp->next;
	} while(temp != all_place);
	return 0;
}

void see_rooms(struct rooms *room)
{
	struct rooms *temp = room;
	if(!room)
	{
		printf("Room isn't create!\n");
		return;
	}
	do
	{
		printf("\tCurrent room is %d\n",temp->room);
		see_bed_place(temp->place);
		temp = temp->next;
	} while(temp != NULL);
}

int see_floors(struct hotel_floor *floor)
{
	struct hotel_floor *temp = floor;
	if(!floor)
	{
		printf("Hotel isn't create!\n");
		return 0;
	}
	do
	{
		printf("Current floor is %d\n",temp->floor);
		see_rooms(temp->floor_room);
		temp = temp->next;
	} while(temp != floor);
	return 0;
}

void add_bedplace(struct bedplace *newplace)
{
	struct bedplace *temp;
	int amount_place,i;
	temp = (struct bedplace *)malloc(sizeof(struct bedplace));
	if(!temp)
		printf("Memory isn't allocated!");
	do
	{
		printf("Input a number of bedplace in the room: ");
		amount_place = scani();
		if (amount_place > 5 || amount_place < 1)
		{
			printf("Very big(small) number of bedplace, it's unreal, try again\n");
			continue;
		}
		else
			break;
	} while (1);
	for(i = 0;i < amount_place;i++)
	{
		char  choice;
		printf("Y - to write a name of studetn, N - to left free bedplace.\n");
		choice = scanc();
		switch(choice)
		{
			case 'y': case 'Y' :
			{
				printf("Input name of student.\n");
				fgets(temp->name,N,stdin);
				break;
			}
			case 'n': case 'N' :
			{
				temp->name[0] = 0;
				break;
			}
			default:
				printf("Unknown command, name left free.\n");
				temp->name[0] = 0;
		}
		if(!newplace)
		{
			temp->prev = temp;
			temp->next = temp;
			newplace = temp;
		}
		else
		{
			struct bedplace *tail = newplace->prev;
			temp->next = tail->next;
			temp->prev = tail;
			tail->next->prev = temp;
			tail->next = temp;
		}
	}
}

void add_rooms(struct rooms **newRoom, int current_room)
{
	struct rooms *temp;
	temp = (struct rooms *)calloc(sizeof(struct rooms),1);
	if(!temp)
	{
		printf("Memory isn't allocated!");
		return;
	}
	temp->room = current_room;
	if(!newRoom)
	{
		temp->next = (*newRoom);
		(*newRoom) = temp;
		add_bedplace(&(*newRoom)->place);
	}
	else
	{
		temp->next = (*newRoom);
		(*newRoom) = temp;
		add_bedplace(&(*newRoom)->place);
	}
}

void add_floor(struct hotel_floor **floor, int current_floor)
{
	struct hotel_floor *temp;
	int amount_rooms,i;
	temp = (struct hotel_floor *)calloc(sizeof(struct hotel_floor),1);
	if(!temp)
		printf("Memory isn't allocated!");
	do
	{
		printf("Input a number of rooms on the [%d] stage: ",current_floor);
		amount_rooms = scani();
		if (amount_rooms > 150 || amount_rooms < 1)
		{
			printf("Very big(small) number of rooms, it's unreal, try again\n");
			continue;
		}
		else
			break;
	} while (1);
	temp->floor = current_floor;
	if(!*floor)
	{
		temp->prev = temp;
		temp->next = temp;
		(*floor) = temp;
		for(i=0;i<amount_rooms;i++)
		{
			add_rooms(&(*floor)->floor_room,i+1);
		}
	}
	else
	{
		struct hotel_floor *tail = (*floor)->prev;
		temp->next = tail->next;
		temp->prev = tail;
		tail->next->prev = temp;
		tail->next = temp;
		for(i=0;i<amount_rooms;i++)
		{
			add_rooms(&temp->floor_room,i+1);
		}
	}
}

int delete_allbedplace(struct bedplace *place)
{
	if(!place)
	{
		printf("Hotel isn't create!\n");
		return 0;
	}
	do
	{
		struct bedplace *temp = place;
		temp->next->prev = temp->prev;
		temp->prev->next = temp->next;
		if(temp == place && place->prev != place)
			place = temp->next;
		if(temp->prev == temp && temp == place)
			place = NULL;
		free(temp);
	} while(place != NULL);
	return 0;
}

int delete_allrooms(struct rooms *room)
{
	if(!room)
	{
		printf("Hotel isn't create!\n");
		return 0;
	}
	do
	{
		struct rooms *temp = room;
		delete_allbedplace(room->place);
		room = room->next;
		free(temp);
	} while(room != NULL);
	return 0;
}

int delete_allfloors(struct hotel_floor *floor)
{
	if(!floor)
	{
		printf("Hotel isn't create!\n");
		return 0;
	}
	do
	{
		struct hotel_floor *temp = floor;
		delete_allrooms(floor->floor_room);
		temp->next->prev = temp->prev;
		temp->prev->next = temp->next;
		if(temp == floor && floor->prev != floor)
			floor = temp->next;
		if(temp->prev == temp && temp == floor)
			floor = NULL;
		free(temp);
	} while(floor != NULL);
	return 0;
}

int find_free_place(struct hotel_floor *floor)
{
	struct hotel_floor *temp = floor;
	struct rooms *temp_room;
	struct bedplace *bed;
	bool findings = false;
	do
	{
		temp_room = temp->floor_room;
		do
		{
			bed = temp_room->place;
			do
			{
				if(bed->name[0] == 0)
				{
					printf("Free place find: %d stage , %d room\n",temp->floor,temp_room->room);
					findings = true;
				}
				bed = bed->next;
			} while (bed != temp_room->place && !findings);
			temp_room = temp_room->next;
		} while (temp_room != NULL && !findings);
		temp = temp->next;
	} while(temp != floor && !findings);
	if(findings == false)
	{
		printf("Sorry, there is no free place.\n");
	}
	return 0;
}

int find_give_free_place(struct hotel_floor *floor)
{
	struct hotel_floor *temp = floor;
	struct rooms *temp_room;
	struct bedplace *bed;
	char *new_student;
	bool findings = false;
	do
	{
		temp_room = temp->floor_room;
		do
		{
			bed = temp_room->place;
			do
			{
				if(bed->name[0] == 0)
				{
					new_student = temp_room->place->name;
					findings = true;
				}
				bed = bed->next;
			} while (bed != temp_room->place && !findings);
			temp_room = temp_room->next;
		} while (temp_room != NULL && !findings);
		temp = temp->next;
	} while(temp != floor && !findings);
	if(findings == false)
	{
		printf("Sorry, there is no free place.\n");
	}
	else
	{
		printf("Input name of student, which get place.\n");
		fgets(new_student,N,stdin);
		printf("Student live in hostel now.\n");
	}
	return 0;
}

int delete_student(struct hotel_floor *floor)
{
	struct hotel_floor *temp = floor;
	struct rooms *temp_room;
	struct bedplace *bed;
	char *delete_student;
	delete_student = (char*)malloc(sizeof(char)*N);
	if(!delete_student)
		return 0;
	bool findings = false;
	printf("Input name of student to delete from hostel.\n");
	fgets(delete_student,N,stdin);
	do
	{
		temp_room = temp->floor_room;
		do
		{
			bed = temp_room->place;
			do
			{
				if(!strcmp(bed->name,delete_student))
				{
					printf("Person deleted.\n");
					bed->name[0] = 0;
					findings = true;
				}
				bed = bed->next;
			} while (bed != temp_room->place && !findings);
			temp_room = temp_room->next;
		} while (temp_room != NULL && !findings);
		temp = temp->next;
	} while(temp != floor && !findings);
	if(findings == false)
	{
		printf("Sorry, this person not found.\n");
	}
	free(delete_student);
	return 0;
}

int resettle_student(struct hotel_floor *floor)
{
	struct hotel_floor *temp = floor;
	struct rooms *temp_room;
	struct bedplace *bed;
	int next_floor,next_room;
	char *delete_student,*stud;
	delete_student = (char*)malloc(sizeof(char)*N);
	if(!delete_student)
		return 0;
	bool findings1 = false,findings2 = false;
	printf("Input name of student to resettle from hostel.\n");
	fgets(delete_student,N,stdin);
	do
	{
		temp_room = temp->floor_room;
		do
		{
			bed = temp_room->place;
			do
			{
				if(!strcmp(bed->name,delete_student))
				{
					stud = bed->name;
					findings1 = true;
				}
				bed = bed->next;
			} while (bed != temp_room->place && !findings1);
			temp_room = temp_room->next;
		} while (temp_room != NULL && !findings1);
		temp = temp->next;
	} while(temp != floor && !findings1);
	if(findings1 == false)
	{
		printf("Sorry, this person not found.\n");
		return 0;
	}
	temp = floor;
	printf("Input floor, where will live student.\n");
	do
	{
		next_floor = scani();
		if (next_floor > 150 || next_floor < 1)
		{
			printf("Very high building, it's unreal, try again\n");
			continue;
		}
		else
			break;
	} while (1);
	printf("Input room, where will live student.\n");
	do
	{
		next_room = scani();
		if (next_room > 150 || next_room < 1)
		{
			printf("Very big(small) number of rooms, it's unreal, try again\n");
			continue;
		}
		else
			break;
	} while (1);
	do
	{
		temp_room = temp->floor_room;
		do
		{
			bed = temp_room->place;
			do
			{	if(temp->floor == next_floor && temp_room->room == next_room && bed->name[0] == 0)
				{
					findings2 = true;
					stud[0] = 0;
					strcpy(bed->name,delete_student);
				}
				bed = bed->next;
			} while (bed != temp_room->place && !findings2);
			temp_room = temp_room->next;
		} while (temp_room != NULL && !findings2);
		temp = temp->next;
	} while(temp != floor && !findings2);
	if(findings2 == false)
	{
		printf("Sorry, this person not found.\n");
	}
	free(delete_student);
	return 0;
}

int information()
{
	printf("\t\tWhat do you want to do?\n");
	printf("-Input 'A' to create hostel.\n");
	printf("-Input 'B' to save hostel in file.\n");
	printf("-Input 'C' to see full information about hostel.\n");
	printf("-Input 'D' to find free place in hostel.\n");
	printf("-Input 'E' to give studet free place.\n");
	printf("-Input 'G' to delete student from hostel.\n");
	printf("-Input 'H' to resettle student.\n");
	printf("-Input 'Q' to exit.\n");
	return 0;
}

int start_menu()
{
	struct hotel_floor *newHotel = NULL;
	while(1)
	{
		char  choice;
		int i,amount_floor;
		information();
		printf("\t\tMake a choice!\n");
		choice = scanc();
		switch (choice)
		{
			case 'A': case 'a':
			{
				printf("Input a number of floor in hostel.\n");
				do
				{
					amount_floor = scani();
					if (amount_floor > 150 || amount_floor < 1)
					{
						printf("Very high building, it's unreal, try again\n");
						continue;
					}
					else
						break;
				} while (1);
				for(i=0;i<amount_floor;i++)
				{
					add_floor(&newHotel,i + 1);
				}
				break;
			};
			case 'B': case 'b':
			{
				if(newHotel == NULL)
					return 0;
				else
				{
					FILE *f;
					f = fopen("Hostel.txt","w+");
					save_floors(newHotel,f);
					printf("Information saved in text file.\n");
					fclose(f);
				}
				break;
			};
			case 'C': case 'c':
			{
				see_floors(newHotel);
				break;
			};
			case 'D': case 'd':
			{
				find_free_place(newHotel);
				break;
			};
			case 'E': case 'e':
			{
				find_give_free_place(newHotel);
				break;
			};
			case 'G': case 'g':
			{
				delete_student(newHotel);
				break;
			};
			case 'H': case 'h':
			{
				resettle_student(newHotel);
				break;
			};
			case 'Q': case 'q':
			{
				delete_allfloors(newHotel);
				return 0;
			};
			default:
			{
				printf("Unknown symbols, try again,please!\n");
			};
			clean_stdin();
		}
	}
	return 0;
}

int main()
{
	start_menu();
	return 0;
}
