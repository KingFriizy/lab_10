#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Trie {
    int count;  // count stores the number of occurrences of a word
    struct Trie *children[26];
};

// Initialize a new Trie node
struct Trie *createNode() {
    struct Trie *node = (struct Trie*) malloc(sizeof(struct Trie));
    node->count = 0;
    for (int i = 0; i < 26; i++)
        node->children[i] = NULL;
    return node;
}

// Insert a word into the Trie
void insert(struct Trie **ppTrie, char *word) {
    struct Trie *curr = *ppTrie;
    if (curr == NULL)
        *ppTrie = createNode();
    curr = *ppTrie;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL)
            curr->children[index] = createNode();
        curr = curr->children[index];
    }
    curr->count++;
}

// Count the number of occurrences of a word in the Trie
int numberOfOccurances(struct Trie *pTrie, char *word) {
    struct Trie *curr = pTrie;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL)
            return 0;
        curr = curr->children[index];
    }
    return curr->count;
}

// Deallocate the Trie
struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie == NULL)
        return NULL;
    for (int i = 0; i < 26; i++)
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    free(pTrie);
    return NULL;
}

int main(void) {
    int numWords = 5;
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    // Insert each word into the Trie
    struct Trie *trie = NULL;
    for (int i = 0; i < numWords; i++)
        insert(&trie, pWords[i]);

    // Count the number of occurrences of each word in the Trie
    for (int i = 0; i < numWords; i++)
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));

    // Deallocate the Trie
    trie = deallocateTrie(trie);
    if (trie != NULL)
        printf("There is an error in this program\n");

    return 0;
}
