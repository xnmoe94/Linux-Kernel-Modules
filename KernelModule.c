#include <linux/list.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/init.h>

#define Num_of_People 5
typedef struct birthday {
	int day;
	int Month;
	int Year;
	struct list_head list;
}birthday;

//We gonna start off by with an Empty LinkedlIst and add Elements
LIST_HEAD(birthday_list);

int birthday_init(void)
{
	struct birthday *person;
	struct birthday *ptr;
	int i;
	printk(KERN_INFO "Loading Modules\n");
	printk(KERN_INFO "INSERTING ELEMENTS INTO THE LINKEDLIST\n");
	for (i = 0; i<Num_of_People; i++)
	{
		//Kmalloc is function for a llocating memory and 
		person = kmalloc(sizeof(*person), GFP_KERNEL);
		person->day = 2 + i;
		person->Month = 8 + i;
		person->Year = 1995 + i;
		//Initializing a list head structure
		INIT_LIST_HEAD(&person->list);
		list_add_tail(&person->list, &birthday_list);
	}
	
	list_for_each_entry(ptr, &birthday_list, list)
	{
	printk(KERN_INFO "Adding Birthdays: day: %d, Month: %d, Year: %d\n",  ptr->day, ptr->Month, ptr->Year);
	}
	printk(KERN_INFO " Done Adding\n");
	return 0;
}

void birthday_exit(void){
	struct birthday *ptr, *next;
	printk(KERN_INFO "REMOVING ELEMENT FROM THE LINKEDLIST\n");
	list_for_each_entry_safe(ptr, next, &birthday_list, list){
	printk(KERN_INFO "Deleting Birthdays: day: %d, Month: %d, Year: %d\n",  
	ptr->day, ptr->Month, ptr->Year);
	//Delete entry from the List
	list_del(&ptr->list);
	// Now we can free the previously allocated memory
	kfree(ptr);
	}
	printk(KERN_INFO "FREE MEMORY\n");
	
}

	


module_init(birthday_init);
module_exit(birthday_exit);

MODULE_LICENSE("MP");
MODULE_DESCRIPTION("SIMPLE PROGRAM THAT PRINT BIRTHDAYS");
MODULE_AUTHOR("MOHAMED ABDULLAHI");






