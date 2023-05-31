 #ifndef EXTRA_H
 #define EXTRA_H
 #include <stdint.h>
 
  class xyz{
    public:
    float x {0};
    float y {0};
    float z {0};

    uint8_t x_id {1};
    uint8_t y_id {1};
    uint8_t z_id {1};

    private:
    
  };

  void print_xyz(xyz data);
#endif