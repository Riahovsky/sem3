#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <ostream>
#include <random>
#include <type_traits>
#include <utility>
#include <vector>

    template<typename Key,typename T>
    class Skip_list {
    private:
        struct Skip_node;                                                       // forward declaration because iterator class needs to know about the node
        std::vector<Skip_node*> head = std::vector<Skip_node*>(1, nullptr);     // element before first element containg pointers to all the first elements of each level
    public:
        using key_type = Key;
        using mapped_type = T;

        using value_type = std::pair<const key_type, mapped_type>;
        using size_type = std::size_t;

        template<typename IT, bool is_const>
        class iterator_base {
        public:
            using node_type = typename std::conditional<is_const, Skip_node const, Skip_node>::type;
            using value_type = typename std::conditional<is_const, IT const, IT>::type;

            iterator_base()
                : curr{ nullptr }
            {
            };

            explicit iterator_base(node_type* pos)
                : curr{ pos }
            {
            };

            iterator_base& operator=(const iterator_base& other)        // copy assignment
            {
                curr = other.curr;
                return *this;
            }

            // the order is determinde by the key so compare by it
            bool operator==(const iterator_base& b) const { return curr == b.curr; }
            bool operator!=(const iterator_base& b) const { return curr != b.curr; }

            bool operator>(const iterator_base& b) const {
                ////assume nullptr is the biggest element
                if (curr != nullptr && b.curr != nullptr)
                    return curr->value.first > b.curr->value.first;
                else if (curr == nullptr && b.curr != nullptr)
                    return true;
                else    // (curr != nullptr && b == nullptr)
                    return false;
            }

            bool operator<(const iterator_base& b) const 
            {
                return (!(curr < b.curr) && (curr != b.curr));
            }

            bool operator>=(const iterator_base& b) const 
            {
                return ((curr == b.curr) || (b.curr > curr));
            }

            bool operator<=(const iterator_base& b) const 
            {
                return ((curr == b.curr) || (b.curr < curr));
            }

            iterator_base& operator++()
            // if next element is empty dont increase more
            {
                if (curr == nullptr)
                    return *this;

                curr = curr->next[0];
                return *this;
            }

            iterator_base& operator+=(const int offset)
            {
                if (offset <= 0) return *this;

                for (int i = 0; i < offset; ++i)
                    ++*this;

                return *this;
            }

            iterator_base operator+(const int offset)
            {
                iterator_base it = *this;
                it += offset;
                return it;
            }

            value_type& operator*() { return curr->value; }
            value_type* operator->() { return &curr->value; }

        private:
            node_type* curr;

            friend class Skip_list;     // to access curr in skiplist functions
        };

        using iterator = iterator_base<value_type,false>;
        using const_iterator = iterator_base<value_type const,true>;

        Skip_list() = default;                  // constructor

        ~Skip_list() noexcept                   // destructor
        {
            free_all_nodes(head[0]);
        }

        Skip_list(const Skip_list& other)               // copy constructor
        {
            try {
                copy_nodes(other);
            }
            catch (...) {                   // if copy constructor fails, clean up mess and re-throw
                free_all_nodes(head[0]);
                throw;
            }
        }

        Skip_list& operator=(const Skip_list& other)        // copy assignment
        {
            auto backup = std::move(head);  // keep backup to provide better exception guarantee

            try {
                copy_nodes(other);
            }
            catch (...) {
                free_all_nodes(head[0]);
                head = std::move(backup);
                throw;
            }

            free_all_nodes(backup[0]);

            return *this;
        }

        Skip_list(Skip_list&& other) noexcept                       // move constructor
            :head{ std::move(other.head) }
        {
            other.head.assign(1, nullptr);
        }

        Skip_list& operator=(Skip_list&& other) noexcept            // move assignment
        {
            if (this != &other) {
                free_all_nodes(head[0]);
                head = std::move(other.head);
                other.head.assign(1, nullptr);
            }

            return *this;
        }

        // ------------Iterators
        iterator begin() noexcept 
        {
            return iterator{ head[0] };
        }

        iterator end() noexcept
        {
            return iterator{ nullptr };
        }

        const_iterator begin() const noexcept
        {
            return const_iterator{ head[0] };
        }

        const_iterator end() const noexcept
        {
            return const_iterator{ nullptr };
        }

        const_iterator cbegin() const noexcept
        {
            return begin();
        }

        const_iterator cend() const noexcept
        {
            return end();
        }

        // ------------capacity
        bool empty() const noexcept
        {
            return (head[0] == nullptr);
        }

        size_type size() const noexcept         // return count of nodes
        {
            Skip_list<Key, T>::size_type counter = Skip_list<Key, T>::size_type{};

            for (auto index = head[0]; index != nullptr; index = index->next[0], ++counter);

            return counter;
        }

        size_type max_size() const noexcept
        {
            return size_type{ static_cast<size_type>(-1) };
        }

        // ------------element access
        mapped_type& operator[] (const key_type& key)
        {
            return find(key)->second;
        }
        mapped_type& operator[] (key_type&& key)
        {
            return find(key)->second;
        }

        // ------------modifiers
        std::pair<iterator, bool> insert(const value_type& value);
        size_type erase(const key_type& key);   // search for an element and erase it from the skip list

        void clear() noexcept               // erase all elements 
        {
            free_all_nodes(head[0]);
            head.assign(1, nullptr);
        }

        // ------------Operations
        iterator find(const key_type& key);
        const_iterator find(const key_type& key) const;

        size_type count(const key_type& key) const
        {
            return find(key) != end() ? 1 : 0;
        }

        size_type top_level() const { return head.size(); }     // maximum height the Skip_list has reached

        void debug_print(std::ostream& os) const;           // show all the levels for debug only. can this be put into skiplist_unit_tests ?
    private:
        size_type generate_level() const;
        static bool next_level() noexcept;

        struct Skip_node{
            value_type value;       // key / T
            size_type levels;
            Skip_node* next[1];
        };

        static Skip_node* allocate_node(value_type value, size_type levels);
        static void free_node(Skip_node* node);

        void copy_nodes(const Skip_list& other);                    
        static void free_all_nodes(Skip_node* head) noexcept;       
    };

    template<typename Key, typename T>
    std::pair<typename Skip_list<Key,T>::iterator, bool> Skip_list<Key,T>::insert(const value_type& value)
        // if key is already present the position of that key is returned and false for no insert
        //
        // if new key inserted or value of given key was replaced return next pos as iterator and indicate change with true
        // otherwise return iterator end() and false
    {
        const auto insert_level = generate_level();     // top level of new node
        const auto insert_node = allocate_node(value, insert_level);
        Skip_list::Skip_node* old_node = nullptr;

        while (head.size() < insert_level) {
            head.push_back(nullptr);
        }

        auto level = head.size();
        auto next = head.data();

        Skip_list::iterator insert_pos;
        bool added = false;

        while (level > 0) {
            const auto index = level - 1;
            auto node = next[index];

            if (node == nullptr || node->value.first > value.first) {   //compare by key

                if (level <= insert_level) {

                    insert_node->next[index] = next[index];
                    next[index] = insert_node;

                    if (!added) {
                        insert_pos = Skip_list::iterator{ next[index] };
                        added = true;
                    }
                }
                --level;
            }
            else if (node->value.first == value.first) {
                // key already present, keep node with more levels
                //  -> no need to insert new node into list if not needed
                //  -> if insert_node->levels > node->levels, we already modified the list
                //     so continuing and removing the other node seems like the easier option
                //     (compared to retracing where links to insert_node have been made)

                if (node->levels >= insert_level) {
                    node->value.second = value.second;
                    free_node(insert_node);

                    return std::make_pair(Skip_list::iterator{ node }, true);
                }

                old_node = node;

                insert_node->next[index] = node->next[index];
                next[index] = insert_node;
                --level;
            }
            else {
                next = node->next;
            }
        }

        if (old_node != nullptr) {
            free_node(old_node);
        }

        return std::make_pair(insert_pos, added);
    }

    template<typename Key, typename T>
    typename Skip_list<Key,T>::size_type Skip_list<Key,T>::erase(const key_type& key)
        // starts search on the highest lvl of the Skip_list
        // if a node with the erase key is found the algorithm goes 
        // down until the lowest lvl.
        // on the way down all links with the key in the list are removed
        // on the lowest lvl the current node which contains the erase key is deleted
        //
        // the return type indicates how many elements are deleted (like std::map)
        // it can become only 0 or 1
    {
        Skip_node* node = nullptr;

        auto level = head.size();
        auto next = head.data();

        while (level > 0) {

            const auto link_index = level - 1;

            if (!next[link_index] || next[link_index]->value.first > key) {
                --level;
            }
            else if (next[link_index]->value.first == key) {
                node = next[link_index];
                next[link_index] = node->next[link_index];
                --level;
            }
            else {
                next = next[link_index]->next;
            }
        }

        while (head.size() > 1 && head.back() == nullptr) head.pop_back();

        if (node) {     // element to erase was found and taken out of list
            free_node(node);
            return 1;
        }
        else {
            return 0;
        }
    }

    template<typename Key, typename T>
    typename Skip_list<Key,T>::const_iterator Skip_list<Key,T>::find(const key_type& key) const
        // first it is iterated horizontal and vertical until the last level is reached
        // on the last level if the keys match the iterator pointing to it is returned
    {
        auto level = head.size();
        auto next = head.data();

        while (level > 0) {
            const auto index = level - 1;

            if (!next[index] || next[index]->value.first > key) {
                --level;
            }
            else if (next[index]->value.first == key) {
                return const_iterator{ next[index] };
            }
            else {
                next = next[index]->next;
            }
        }
        return end();
    }

    template<typename Key, typename T>
    typename Skip_list<Key,T>::iterator Skip_list<Key,T>::find(const key_type& key)
        // same as const_iterator function, is there a way to not have this redundant?
    {
        auto level = head.size();
        auto next = head.data();

        while (level > 0) {
            const auto index = level - 1;

            if (!next[index] || next[index]->value.first > key) {
                --level;
            }
            else if (next[index]->value.first == key) {
                return iterator{ next[index] };
            }
            else {
                next = next[index]->next;
            }
        }
        return end();
    }

    template<typename Key, typename T>
    void Skip_list<Key,T>::debug_print(std::ostream& os) const
        //messy debug routine to print with all available layers
    {
        if (head[0] == nullptr) {
            os << "empty" << '\n';
            return;
        }

        auto level = head.size();
        auto next = head.data();

        os << "lvl: " << level << " ";

        while (level > 0) {

            const auto index = level - 1;

            if (!next[index]) {
                os << '\n';
                --level;

                if (level > 0) {
                    os << "lvl: " << index << " ";
                    next = head.data();     // point back to begining
                }
            }
            else {
                os << next[index]->value.first << '/' << next[index]->value.second << ' ';
                next = next[index]->next;
            }
        }
    }

    template<typename Key, typename T>
    typename Skip_list<Key,T>::size_type Skip_list<Key,T>::generate_level() const
        // generate height of new node
    {
        size_type new_node_level = size_type{};

        do {
            ++new_node_level;
        } while (new_node_level <= head.size() && next_level());

        return new_node_level;
    }

    template<typename Key, typename T>
    bool Skip_list<Key,T>::next_level() noexcept
        // arround 50% chance that next level is reached
    {
        static auto engine = std::mt19937{ std::random_device{}() };
        static auto value = std::mt19937::result_type{ 0 };
        static auto bit = std::mt19937::word_size;

        if (bit >= std::mt19937::word_size) {
            value = engine();
            bit = 0;
        }

        const auto mask = std::mt19937::result_type{ 1 } << (bit++);
        return value & mask;
    }

    template<typename Key, typename T>
    typename Skip_list<Key,T>::Skip_node* Skip_list<Key, T>::allocate_node(value_type value, size_type levels)
    {
        const auto node_size = sizeof(Skip_node) + (levels - 1) * sizeof(Skip_node*);
#ifdef _MSC_VER         // Visual Studio doesnt support  aligned alloc yet ( new in C++ 17)
        const auto node = _aligned_malloc(node_size, alignof(Skip_node));
#else
        const auto node = std::aligned_alloc(alignof(skip_node), node_size);
#endif
        new(node) Skip_node{ value, levels, nullptr };

        return reinterpret_cast<Skip_node*>(node);
    }

    template<typename Key, typename T>
    void Skip_list<Key,T>::free_node(Skip_node* node)
    {
        node->~Skip_node(); // proper destroy potentially dynamicall alocatet types in skip_node

#ifdef _MSC_VER
        _aligned_free(node);
#else
        std::free(node);
#endif
    }

    template<typename Key, typename T>
    void Skip_list<Key,T>::copy_nodes(const Skip_list& other)
        // precondition: head isn't owner of any nodes
    {
        head.assign(other.head.size(), nullptr);

        auto tail = std::vector<Skip_node**>{};

        tail.reserve(head.size());
        std::for_each(std::begin(head), std::end(head), [&](auto&& link) { tail.push_back(&link); });

        for (auto node = other.head[0]; node != nullptr; node = node->next[0]) {
            const auto copy_node = allocate_node(node->value, node->levels);

            for (auto i = 0u; i < copy_node->levels; ++i) {
                *tail[i] = copy_node;
                tail[i] = &copy_node->next[i];
            }
        }

        std::for_each(std::begin(tail), std::end(tail), [](auto link) { *link = nullptr; });
    }

    template<typename Key, typename T>
    void Skip_list<Key,T>::free_all_nodes(Skip_node* head) noexcept
    {
        for (auto index = head; index != nullptr;) {
            const auto temp = index;
            index = index->next[0];
            free_node(temp);
        }
    }
}
#endif