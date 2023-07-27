    /* state-machine NLP example */

    #include <stdio.h>
	#include <string.h>

    #define MAX 100

    #define NOUN 1

    #define VERB 2

    #define ADJ 3

    #define ADV 4

    #define DET 5

    #define PREP 6

    #define TERM 7

    #define STARTUP -1

    /* structure of the word database (wdb) */

    struct word {

        char word[20];

        char type;

    };

    struct word wdb[MAX];  /* array of db structure */

    int db_pos=0;               /* number of entries in wdb */

    char state=STARTUP;    /* holds the current state of the machine */

    char s[80];                 /* holds the sentence */

    char *t_pos=0;             /* points into the sentence */

    char token[80];           /* contains the word */

    void main()

    {

        setup();

		strcpy(s, "the child runs quickly to the large house .");
		//strcpy(s, "the child window quickly to the large house .");
		parser(s);

    }
	

    /* Context-free recursive-descent NLP parser */

    int parse(char* s)

    {

        if (!nounphrase(s)) return 0;

        if (!verbphrase(s)) return 0;

        if (!terminator (s)) return 0;

        return 1;

    }

    /* read a noun phrase from the input stream */

    int nounphrase(char* s)

    {

        char type;

        //get_token();
		char* token = strtok(s, " ");
		
        type=find_type(token);
		
		

        switch(type) {

            case DET :

                //get_token();
				token = strtok(NULL, " ");
				char* token = strtok(s, " ");

                type=find_type(token);
				
				

                if (type=NOUN) return 1;

                else if (type==ADJ) {

                    //get_token();
					token = strtok(NULL, " ");
					char* token = strtok(s, " ");


                    type=find_type(token);

                    if (type==NOUN) return 1;

                }

                break;

            case PREP :

                return nounphrase(s);

            }

            return 0;

    }

    /* read a verb phrase */

    int verbphrase(char* s)

    {

        char type, *pos:

        //get_token();
		token = strtok(NULL, " ");
		char* token = strtok(s, " ");


        type=find_type(token);

        if (type!=VERB) return 0;    /* must start with a verb */

        pos=t_pos;                     /* save current position for backtracking */

        /* verb + adverb + NP */

        if (verb_adv_np(s)) return 1;

        /* verb + NP */

        t_pos=pos;                     /* back up */

        if (verb_np(s)) return 1;

        /* verb + adverb -- no NP */

        t_pos=pos;

        if (verb_adv(s)) return 1;

        /* just adverb */

        return 1;

    }

    int verb_np(char* s)

    {

        /* verb + NP */

        return nounphrase(s);

    }

    int verb_adv_np(char* s)

    {

        char type;

        //get_token();
		
		token = strtok(NULL, " ");
		char* token = strtok(s, " ");

        type=find_type(token);

        if (type==ADV && nounphrase(s)) return 1;

        return 0;

    }

    int verb_adv(char* s)

    {

        char type;

        //get_token();
		
		token = strtok(NULL, " ");
		char* token = strtok(s, " ");

        type=find_type(token);

        return(type==ADV);

    }

    int terminator(char* s)

    {

        //get_token();
		
		token = strtok(NULL, " ");
		char* token = strtok(s, " ");

        return(find_type(token)==TERM);

    }


    /* find the type G1ven the word */

    find_type(word)

    char *word;

    {

        int t;

        for(t=0 ; t<db_pos ; t++)

            if(!strcmp(word, wdb[t].word))

                return wdb[t].type;

            return 0;

    }
	

    void setup()

    {

        assert_wdb("door", NOUN);

        assert_wdb("window", NOUN);

        assert_wdb("house", NOUN);

        assert_wdb("child", NOUN);

        assert_wdb("has", VERB);

        assert_wdb("runs", VERB);

        assert_wdb("plays", VERB);

        assert_wdb("large", ADJ);

        assert_wdb("quickly", ADV);

        assert_wdb("the", DET);

        assert_wdb("a", DET);

        assert_wdb("to", PREP);

        assert_wdb(".", TERM);

    }

    /* place facts into database */

    void assert_wdb(word, type){

        if (db_pos<MAX) {

            strcpy(wdb[db_pos].word, (char*)word);

            wdb[db_pos].type=type;

            db_pos++;

        }

        else printf("Word database full. \n");

    }
	
    