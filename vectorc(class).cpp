template<typename T>
class vectorc{
private:
  size_t mycapacity;
  size_t n_size;
  T* buffer;

public:

  typedef T* iterator;

  vectorc(): n_size(0), mycapacity(0){
    buffer = (T*)calloc(mycapacity, sizeof(T));
  }
  vectorc(size_t _n): n_size(_n), mycapacity(_n){
    buffer = (T*)calloc(mycapacity, sizeof(T));
  }
  vectorc(size_t _n, T val): n_size(_n), mycapacity(_n){
    buffer = (T*)calloc(mycapacity, sizeof(T));
    fill(buffer, buffer + n_size, val);
  }

  void assign(size_t _n, T val){
    mycapacity = n_size = _n;
    buffer = (T*)realloc(buffer, sizeof(T) * mycapacity);
    fill(buffer, buffer + n_size, val);
  }
  void resize(size_t _n){
    mycapacity = n_size = _n;
    buffer = (T*)realloc(buffer, sizeof(T) * mycapacity);
  }
  void clear(){
    *this.resize(0);
  }
  size_t capacity(){
    return mycapacity;
  }
  size_t size(){
    return n_size;
  }
  size_t length(){
    return n_size;
  }
  bool empty(){
    return (bool)(n_size == 0);
  }
  void push_back(T val){
    if(n_size == mycapacity){
      mycapacity <<= 1;
      if(!mycapacity) mycapacity = 1;
      buffer = (T*)realloc(buffer, sizeof(T) * mycapacity);
    }
    *(buffer + n_size++) = val;
  }
  void reserve(size_t cap){
    if(cap <= mycapacity) return;
    mycapacity = cap;
    buffer = (T*)realloc(buffer, sizeof(T) * mycapacity);
  }
  void shrink_to_fit(){
    mycapacity = n_size;
    buffer = (T*)realloc(buffer, sizeof(T) * mycapacity);
  }
  size_t max_size(){
    return ((size_t(4) * size_t(1024) * size_t(1024) * size_t(1024LL)) / size_t(sizeof(T))) - size_t(1);
  }
  void pop_back(){
    if(empty()) return;
    (buffer + n_size--) = 0;
  }
  T& operator[](size_t pos){
    if(pos >= 0 && pos < n_size) return buffer[pos];
    throw std::out_of_range("index out of bound!!\n");
  }
  T* data(){
    return buffer;
  }
  vectorc<T>& operator = (const vectorc<T>& v){
    mycapacity = n_size = v.size();
    buffer = (T*)realloc(buffer, sizeof(T) * mycapacity);
    memcpy(buffer, v.data(), sizeof(T) * mycapacity);
  }

  T& at(size_t pos){
    if(pos >= 0 && pos < n_size) return buffer[pos];
    throw std::out_of_range("index out of bound!!\n");
  }
  T& front(){
    if(empty()) throw std::out_of_range("index out of bound!!\n");
    return buffer[0];
  }
  T& back(){
    if(empty()) throw std::out_of_range("index out of bound!!\n");
    return buffer[n_size - 1];
  }
  void swap(vectorc<T>& v){
    swap(*this, v);
  }
  iterator begin(){
    return buffer;
  }
  iterator end(){
    return buffer + n_size;
  }

};
