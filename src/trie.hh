class Trie
{
public:
    bool isLeaf;
    Trie* character[CHAR_SIZE];

    // Constructor
    Trie()
    {
        this->isLeaf = false;

        for (int i = 0; i < CHAR_SIZE; i++)
            this->character[i] = nullptr;
    }

    void insert(std::string);
    bool deletion(Trie*&, std::string);
    bool search(std::string);
    bool haveChildren(Trie const*);
};