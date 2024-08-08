#include <gtest/gtest.h>
#include <memory>

struct User {
  User(const std::string &name) : name_(name) {}
  std::string name_;
};

// placement new as new
TEST(PlacementNew, MallocAllocate) {
  auto *memory = std::malloc(sizeof(User));
  auto *user = new (memory) User("John");

  ASSERT_EQ("John", user->name_);

  user->~User();
  std::free(memory);
}

// c++17 version
TEST(PlacementNew, UnitializedFill) {
  auto *memory = std::malloc(sizeof(User));
  auto *user_ptr = reinterpret_cast<User *>(memory);
  std::uninitialized_fill_n(user_ptr, 1, User{"Rei"});

  ASSERT_EQ("Rei", user_ptr->name_);

  std::destroy_at(user_ptr);
  std::free(memory);
}

TEST(PlacementNew, ConstructAt) {
  auto *memory = std::malloc(sizeof(User));
  auto *user_ptr = reinterpret_cast<User *>(memory);
  std::construct_at(user_ptr, User{"Mizuiro"});

  ASSERT_EQ("Mizuiro", user_ptr->name_);

  std::destroy_at(user_ptr);
  std::free(memory);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}