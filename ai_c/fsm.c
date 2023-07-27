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

    char* token;           /* contains the word */

    void main()

    {

        setup();

		strcpy(s, "the child runs quickly to the large house .");
		//strcpy(s, "the child window quickly to the large house .");
		parse(s);

    }
	void parse(char* s){
		token = strtok(s, " ");
			while (token) {
				state = is_legal(token, state);
				printf("state: %d\n", state);
				if (state==0) {
					printf("Error in sentence. \n");
					return 0;
				}
				token = strtok(NULL, " ");
			}
		
		
	}
	/* check for valid state transitions */

    is_legal(word, state)

    char *word;

    int state;

    {

        int type;

        type=find_type(word);

        if (type==DET) return state;   /* skip */

        if (type==TERM) return TERM;   /* end of sentence */

        switch(state) {

            case STARTUP : if (type!=DET) return type;

                else return STARTUP;

            case NOUN :

                if (type==VERB) return VERB;

                if (type==PREP) return PREP;

                break;

            case VERB :

                if (type==PREP) return PREP;

                if (type==NOUN) return NOUN;

                if (type==ADV) return ADV;

                if (type==ADJ) return ADJ;

                break;

            case ADV :

                if (type==NOUN) return NOUN;

                if (type==PREP) return PREP;

                break;

            case ADJ :

                if (type==NOUN) return NOUN;

                break;

            case PREP :

                if (type==ADJ) return ADJ;

                if (type==NOUN) return NOUN;

                break;

        }

        return 0;

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
	
    