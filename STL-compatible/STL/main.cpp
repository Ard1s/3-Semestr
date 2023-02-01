template<typename T>
class MyContainer {
public:
    // Types
    typedef T value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    typedef std::size_t size_type;

    // Constructors
    MyContainer();
    explicit MyContainer(size_type count);
    MyContainer(size_type count, const value_type& value);
    template<typename InputIt>
    MyContainer(InputIt first, InputIt last);
    MyContainer(const MyContainer& other);
    MyContainer(MyContainer&& other) noexcept;

    // Destructor
    ~MyContainer();

    // Assignment operators
    MyContainer& operator=(const MyContainer& other);
    MyContainer& operator=(MyContainer&& other) noexcept;

    // Iterators
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    // Capacity
    bool empty() const;
    size_type size() const;
    size_type max_size() const;

    // Element access
    reference operator[](size_type index);
    const_reference operator[](size_type index) const;
    reference at(size_type index);
    const_reference at(size_type index) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    // Modifiers
    void clear() noexcept;
    iterator insert(const_iterator pos, const value_type& value);
    iterator insert(const_iterator pos, value_type&& value);
    iterator insert(const_iterator pos, size_type count, const value_type& value);
    template<typename InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last);
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);
    void push_back(const value_type& value);
    void push_back(value_type&& value);
    void pop_back();
    void resize(size_type count);
    void resize(size_type count, const value_type& value);
    void swap(MyContainer& other) noexcept;

private:
    // Implementation details
};
