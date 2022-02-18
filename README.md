# lynks
A more pythonic way to work with lists in C.
1. Create the first lynk, essentially instantiating the list OR create "array" of empty lynks (see lynkarr(<size>)).
    1a. lynk *list_one = lynkempty() | returns a lynk pointer to an empty lynk.
        i. the data struct can hold either ints or bools or strings or char, or all four. TODO: Implementing nested linked lists and arrays.
    1b. lynk *list_two = lynkint(<int you would like in this lynk>); | returns a lynk pointer to a lynk with an integer in it.
    1c. lynk *list_three = lynkstr(<str you would like in this lynk>); | returns a lynk pointer to a lynk with a string in it.  | For memory sake, limiting characters to 1000
    1d. lynk *list_four = lynkchar(<char you would like in this lynk>); | returns a lynk pointer to a lynk with a char in it.
    1e. lynk *list_five = lynkbool(<bool you would like in this lynk>); | returns a lynk pointer to a lynk with a bool in it.
    1f. lynk *list_six = lynkall(<int>, <str>, <char>, <bool>) | returns a lynk pointer to a lynk with an int, string, character, and bool value in it.
        i. For lynkall(), if you would only like two, or three values populated, like a lynk with an int and a string, instantiate it with throwaway default values like this:
        ii. Ex:
            lynk *list_seven = lynkallcreate(-1, "real value", '\0', true);
        iii. ("lynk *list_num = " is an arbitrary example of how these lynk lists might be instantiated.)
    1g. Created lynk is malloc()'d, so it will need to be free'd later with either lynkunload() or lynkremove(), or even manually with free() though this may cause issues (See further down readme).
    1h. lynk *list eight = lynkarr(<quantity of lynks in "array">) | Returns a lynk as the head of a lynk list of N elements.

2. Adding lynks to the linked list.
    1. lynkinsert(<takes address of (&) pointer to first link>, <index in list where you want lynk inserted>, <lynk you want inserted, can be product of lynkempty() or other lynk create functions>); | Inserts lynk at index of linked list.
        i. Can be used with a loop/iterator like this:
            Ex:
            for (int x = 0; x < 10; x++)
            {
                lynkinsert(&list_six, x, lynkall(69, "fourtwenty", 'y', true));
            }
        ii. If lynk is already existing at index, they are pushed to the right
    2. lynkback(<takes address of (&) pointer to first link>, <lynk you want inserted>) | Inserts lynk at the end of the linked list, wherever that is.
        i. Can be used with a loop/iterator like this:
        ii. Ex:
            for (int x = 0; x < 10; x++) // Can start loop at any value since iterator doesnt matter in regards to function input. Every call inserts at the last populated index + 1.
            {
                lynkback(&list_six, lynkall(69, "fourtwenty", 'y', true));
            }
            //This loop will add 10 lynks to the end of the linked list
    3. lynkfront(<takes address of (&) pointer to first link>, <lynk you want inserted>) | Inserts lynk at the 0 index, front of the list.
        i. Can be used with a loop/iterator like this:
        ii. Ex:
                for (int x = 0; x < 10; x++) // Can start loop at any value since iterator doesnt matter in regards to function input. Every call inserts at the last populated index 0, and shifts all others to the right.
                {
                    lynkfront(&list_six, lynkall(69, "fourtwenty", 'y', true));
                }
                //This loop will add 10 lynks to the beginning of the linked list

3. Size/Count function. Returning int of lynks loaded, including and following the specified lynk.
    1. int lynkcount(<takes *lynk pointer, iterates through all lynks in linked list following this one, adding +1 to count, then returning count when NULL is reached>);
    2. int lynksize (returns an integer of the size of the entire array stored at the head lynk, saving the iteration of the above process which is very slow.)


4. TODO: Potentially a sort system, creates a new linked list of newly created lynks with sorted values relative to old list. Does not unload old list.

5. Lynk selection function
    1. lynkgoto(<takes *lynk pointer>, <takes index of lynk you would like selected>)
        i. Example of looping through 10 lynks in list_1 to get the sum of it's integer values.
        ii. Ex:
            int sum = 0;
            for (int x = 0; x < 10; x++)
            {
                sum += lynkgoto(list_1, x)->intval;
            }
            return sum;
            // If there is nothing at specified index (x), it will return NULL and then produce unexpected results, like segmentation faults.

6. Lynk removal function
    1. lynkpop(<takes address of (&) pointer to first link>, <takes index in lynk list that lynk is to be removed>);
        i. Goes to lynk at index + 1, saves to temp *variable if not NULL, else saves NULL. | lynk *tmp_1 = lynkgoto(list_1, i + 1);
        ii. Goes to lynk at index - 1, saves to temp *variable. lynk *tmp_2 = lynkgoto(list_1, i - 1);
        iii. Goes to lynk at index, unload with free().
        iiii. Goes to lynk at index - 1 (tmp_1), tmp_2->next = tmp_1
    2. lynkpopback(<takes address of (&) pointer to first link>); | Removes lynk off the end of linked list | lynkremove(list_1, lynksize(list_1));
    3. lynkpopfront(<takes address of (&) pointer to first link>); | Removes lynk at front the end of linked list
        i. Goes to lynk at index 1 (which would be list_1 in above example), saves to temp *variable if not NULL, else saves NULL. | lynk *tmp_1 = lynkgoto(list_1, 1);
        ii. free(lynkgoto(list_1, 0) or simply list_1)
        iii. Reassign the list_1 pointer to tmp_1
        iiii. The lynk that was originally list_1 has been free'd from memory, and replaced with the lynk that was immediately after it.

7. Lynk unload function
    1. lynkunload(<takes *lynk pointer>)
        i. Goes through each lynk in linked list, from back to front, and frees them.
        ii. Ex:
            for (int x = lynksize(list_1) - 1, x >= 0, x--)
            {
                free(lynkgoto(list_1, x));
            }
        ii. Could also do it recursively, however foundation needs to be built before implementation.


