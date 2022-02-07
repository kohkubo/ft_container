#ifndef INCLUDES_TREE_UTIL_HPP_
#define INCLUDES_TREE_UTIL_HPP_

#include <iostream>
#define END            "\033[0m"
#define BOLD           "\033[1m"
#define BLACK          "\033[30m"
#define RED            "\033[31m"
#define GREEN          "\033[32m"
#define YELLOW         "\033[33m"
#define BLUE           "\033[34m"
#define MAGENTA        "\033[35m"
#define CYAN           "\033[36m"
#define WHITE          "\033[37m"
#define UNDERLINE      "\033[4m"
#define BOLD_UNDERLINE "\033[1;4m"

namespace ft {

template <class __node_pointer>
inline bool __tree_is_left_child(__node_pointer __x) {
  return __x->__parent_->__left_ == __x;
}

template <class __node_pointer>
inline __node_pointer __tree_min(__node_pointer __x) {
  while (__x->__left_ != NULL) __x = __x->__left_;
  return __x;
}
template <class __node_pointer>
inline __node_pointer __tree_max(__node_pointer __x) {
  while (__x->__right_ != NULL) __x = __x->__right_;
  return __x;
}
template <class __node_pointer>
inline __node_pointer __tree_next(__node_pointer __x) {
  if (__x->__right_ != NULL) {
    return __tree_min(__x->__right_);
  }
  while (!__tree_is_left_child(__x)) {
    __x = __x->__parent_;
  }
  return __x->__parent_;
}
template <class __node_pointer>
inline __node_pointer __tree_prev(__node_pointer __x) {
  if (__x->__left_ != NULL) {
    return __tree_max(__x->__left_);
  }
  while (__tree_is_left_child(__x)) {
    __x = __x->__parent_;
  }
  return __x->__parent_;
}
// __tree_left_rotate
template <class __node_pointer>
void __tree_left_rotate(__node_pointer __x) {
  __node_pointer __y = __x->__right_;
  __x->__right_      = __y->__left_;
  if (__x->__right_ != NULL) {
    __x->__right_->__parent_ = __x;
  }
  __y->__parent_ = __x->__parent_;
  if (__tree_is_left_child(__x)) {
    __x->__parent_->__left_ = __y;
  } else {
    __x->__parent_->__right_ = __y;
  }
  __y->__left_   = __x;
  __x->__parent_ = __y;
}

// __tree_right_rotate
template <class __node_pointer>
void __tree_right_rotate(__node_pointer __x) {
  __node_pointer __y = __x->__left_;
  __x->__left_       = __y->__right_;
  if (__x->__left_ != NULL) {
    __x->__left_->__parent_ = __x;
  }
  __y->__parent_ = __x->__parent_;
  if (__tree_is_left_child(__x)) {
    __x->__parent_->__left_ = __y;
  } else {
    __x->__parent_->__right_ = __y;
  }
  __y->__right_  = __x;
  __x->__parent_ = __y;
}

template <class __node_pointer>
void print_node(__node_pointer __nd) {
  if (__nd == NULL) {
    std::cout << "NULL" << std::endl;
    return;
  }
  std::cout << "node: " << __nd << std::endl;
  std::cout << __nd->__value_.first << " " << __nd->__value_.second
            << std::endl;
  std::cout << " parent: " << __nd->__parent_;
  std::cout << " left: " << __nd->__left_;
  std::cout << " right: " << __nd->__right_;
  std::cout << std::endl;
  std::cout << "==============" << std::endl;
}

// print_tree
template <class __node_pointer>
void print_tree(__node_pointer __nd, size_t __level) {
  if (__nd == NULL) {
    return;
  }
  print_tree(__nd->__right_, __level + 1);
  for (size_t i = 0; i < __level; i++) {
    std::cout << "  ";
  }
  if (!__nd->__is_black_) {
    std::cout << RED;
  }
  std::cout << __nd->__value_.first << " " << END << std::endl;
  print_tree(__nd->__left_, __level + 1);
}

template <class __node_pointer>
void print_tree_node(__node_pointer __nd) {
  std::cout << "==========================" << std::endl;
  print_tree(__nd, 0);
}

template <class __node_pointer>
void __tree_balance_after_insert(__node_pointer __root, __node_pointer __x) {
  __x->__is_black_ = __x == __root;
  // xがルートではない && xが赤。xの親が赤のとき、ループする
  while (__x != __root && !__x->__parent_->__is_black_) {
    // 新ノードの親が左ノードの場合
    //      P●
    //    Z●

    //       G
    //     P●
    //   Z●

    //        G
    //      P●
    //       Z●
    if (__tree_is_left_child(__x->__parent_)) {
      // 祖父ノードの右を取る
      __node_pointer __y = __x->__parent_->__parent_->__right_;
      // 祖父ノードの右ノードが赤の場合(祖父ノードが黒である必要があるわけではない)
      // 目指す状態
      // 親  黒
      // 祖父 黒 || 赤
      //        G            G
      //      P●   ●       P●   ●
      //    Z●              Z●

      // 祖父ノードがNULLのパターンは親がルートノードであるパターンでしかありえない
      if (__y != NULL && !__y->__is_black_) {
        // rootなら◯でループ終了      G●           G●
        //                      P◯   ◯       P◯   ◯
        //                    Z●              Z●
        // 親ノードを黒にする
        __x              = __x->__parent_;
        __x->__is_black_ = true;
        // 祖父ノードがルートなら黒にする。ルートでないなら赤にする
        __x              = __x->__parent_;
        __x->__is_black_ = __x == __root;

        // 祖父ノードの右は常に黒にする。
        __y->__is_black_ = true;

        // 再度、色を整えるために祖父ノードを対象ノードとして、ループをする。

      } else {
        //         G           G
        //      P●   ◯       P●  ◯
        //    Z●              Z●
        // 祖父ノードの右ノードが黒の場合
        // (祖父ノードは赤である必要があるわけではない)
        // 祖父ノードが黒い場合は、ループを終わることができる
        // 目指す状態
        // 自分 赤
        // 親  黒
        // 祖父 赤
        // 新ノードが右ノードの場合
        if (!__tree_is_left_child(__x)) {
          //            G
          //          P●  ◯
          //           Z●       このケース
          // 回転をして、新ノードを左ノードにする
          __x = __x->__parent_;
          __tree_left_rotate(__x);
          //            G
          //          Z●  ◯
          //        P●
        }

        // 新ノードの親ノードは黒にする(下の処理とセット)
        //            G●              G●
        //          Z◯   ◯          P◯   ◯
        //        P●              Z●
        __x              = __x->__parent_;
        __x->__is_black_ = true;

        // 祖父ノードは赤にする
        __x              = __x->__parent_;
        __x->__is_black_ = false;

        // 祖父ノードと親ノードを反転させる
        // 祖父ノードを右ノードにする

        __tree_right_rotate(__x);
        //            Z◯                P◯
        //          P●  G●            Z●  G●
        //                ◯                  ◯
        break;
      }
      // 新ノードの親が右ノードの場合
    } else {
      // 新ノードの親が、右ノードである場合
      // 祖父ノードの左を取る
      __node_pointer __y = __x->__parent_->__parent_->__left_;

      // 祖父ノードの左ノードが赤の場合
      if (__y != NULL && !__y->__is_black_) {
        // 親は黒にする
        __x              = __x->__parent_;
        __x->__is_black_ = true;
        // 祖父ノードがルートの場合は黒に、それ以外は赤にする
        __x              = __x->__parent_;
        __x->__is_black_ = __x == __root;
        // 祖父ノードの左は常に黒にする。(祖父ノードの子は全て黒だから)
        __y->__is_black_ = true;
      } else {
        // 祖父ノードの左ノードが黒の場合
        if (__tree_is_left_child(__x)) {
          __x = __x->__parent_;
          __tree_right_rotate(__x);
        }
        __x              = __x->__parent_;
        __x->__is_black_ = true;
        __x              = __x->__parent_;
        __x->__is_black_ = false;
        __tree_left_rotate(__x);
        break;
      }
    }
  }
}

template <class __node_pointer>
inline bool __tree_is_black(__node_pointer __x) {
  return __x == NULL || __x->__is_black_;
}

template <class __node_pointer>
void __tree_remove(__node_pointer __root, __node_pointer __z) {
  // zは消去対象ノード
  __node_pointer __y;
  if (__z->__left_ == NULL || __z->__right_ == NULL) {
    // zが最小値の場合
    // 消去対象ノードが、子が1つ、子がない場合
    //      z      z         z
    //    c          c
    __y = __z;
    // yは消去対象ノード
  } else {
    // zが最小値でない場合、最小値の次のノードをyとする
    // zが、子が2つの場合
    // yはzノードの次のノード
    //      z
    //    c   c
    // zが子が2つの場合
    // yはzノードの最小のノード
    __y = __tree_next(__z);
  }

  // xはyのおそらくは、NULLのシングルチャイルド
  // wはおそらく、NULLのおじノードです。wは最終的には、xの兄弟になります。
  // xをyの親にリンクし、wを見つけます

  __node_pointer __x;
  if (__y->__left_ != NULL) {
    // zが自分が最小値で、かつ、左に子がある場合、それをxとする(必ずしも前の子になるわけではない)
    //      z
    //    c
    //     gc
    // この形のパターンのとき、gcをxとする
    __x = __y->__left_;
  } else {
    // それ以外のパターンではxはyの右ノード
    __x = __y->__right_;
  }

  if (__x != NULL) {
    // xがNULLではない場合は、xの親をyの親にする
    //        y       y
    //      x           x
    __x->__parent_ = __y->__parent_;
  }

  __node_pointer __w = NULL;

  // ここからyの上の話。
  // yの切り離し処理を行う
  if (__tree_is_left_child(__y)) {
    // yが左の子の場合、yが親から切り離される
    // 親は leftにxを持つように変更する

    //          P  |         P      親側から見て、子を変更する
    //        y    |       x        yが切り離されて、xになる
    __y->__parent_->__left_ = __x;

    if (__y != __root) {
      // もし、yがルートではないなら
      // wは、yの親の左ノードである。
      //            P      |        P     wに入れる
      //          y        |          w
      __w = __y->__parent_->__right_;
    } else {
      // yがrootなら, rootをxに変更する
      // このとき、wはNULLです。
      __root = __x;
    }
  } else {
    // yが右側の場合
    //        P
    //          y

    // yをに変える
    //       P
    //         x
    //
    //    w に Pの左を入れる
    __y->__parent_->__right_ = __x;
    // yが右の子の場合、rootになることはないです。
    __w                      = __y->__parent_->__left_;
  }

  bool __removed_black = __y->__is_black_;

  // zを切り離し、yに置き換える
  if (__y != __z) {
    // yがzでない場合,つまり、zが現状最小のノードで会った場合
    // yの親はzの親である。
    __y->__parent_ = __z->__parent_;
    if (__tree_is_left_child(__z)) {
      // zが左ノードだった場合、zの親のleftにyを入れる
      __y->__parent_->__left_ = __y;
    } else {
      // zが右ノードだった場合、zの親のrightにyを入れる
      __y->__parent_->__right_ = __y;
    }
    // yはzと入れ替えされる
    __y->__left_            = __z->__left_;
    __y->__left_->__parent_ = __y;
    __y->__right_           = __z->__right_;

    if (__y->__right_ != NULL) {
      __y->__right_->__parent_ = __y;
    }

    __y->__is_black_ = __z->__is_black_;
    if (__root == __z) {
      __root = __y;
    }
  }
  // yが黒で勝つ、 ルートがnullでないなら、
  // つまり、赤を消去した場合、または、最後のノードを消去した場合にはrebalanceを行う必要がないです。
  if (__removed_black && __root != NULL) {
    if (__x != NULL) {
      // xがnullでないなら、xは黒ノードにする
      __x->__is_black_ = true;
    } else {
      while (true) {
        if (!__tree_is_left_child(__w)) {
          // wが右ノードの場合
          if (!__w->__is_black_) {
            // wが赤の場合
            // wを黒にし、親を赤にする
            __w->__is_black_            = true;
            __w->__parent_->__is_black_ = false;
            // wの親の親の位置にwが来る
            __tree_left_rotate(__w->__parent_);
            // ルートがwの左なら, wはルートにする
            if (__root == __w->__left_) {
              // rotateする前、wがルートの親を保つ場合、はルートになる
              __root = __w;
            }
            // wの左の右がwにする
            // くの字の下のところがwになる
            // yがルートになることはないです。
            __w = __w->__left_->__right_;
          }
          if (__tree_is_black(__w->__left_) && __tree_is_black(__w->__right_)) {
            // wの子が全部黒なら、wを赤にする
            __w->__is_black_ = false;
            __x              = __w->__parent_;
            if (__x == __root || !__x->__is_black_) {
              // xがルート、または、xが赤なら、xを黒にする
              __x->__is_black_ = true;
              break;
            }
            if (__tree_is_left_child(__x)) {
              __w = __x->__parent_->__right_;
            } else {
              __w = __x->__parent_->__left_;
            }
          } else {
            // wが赤の子を持つなら
            if (__tree_is_black(__w->__right_)) {
              // wの右が黒なら
              __w->__left_->__is_black_ = true;
              __w->__is_black_          = false;
              __tree_right_rotate(__w);
              __w = __w->__parent_;
            }
            __w->__is_black_            = __w->__parent_->__is_black_;
            __w->__parent_->__is_black_ = true;
            __w->__right_->__is_black_  = true;
            __tree_left_rotate(__w->__parent_);
            break;
          }
        } else {
          if (!__w->__is_black_) {
            __w->__is_black_            = true;
            __w->__parent_->__is_black_ = false;
            __tree_right_rotate(__w->__parent_);
            if (__root == __w->__right_) {
              __root = __w;
            }
            __w = __w->__right_->__left_;
          }
          if (__tree_is_black(__w->__left_) && __tree_is_black(__w->__right_)) {
            __w->__is_black_ = false;
            __x              = __w->__parent_;
            if (!__x->__is_black_ || __x == __root) {
              __x->__is_black_ = true;
              break;
            }
            if (__tree_is_left_child(__x)) {
              __w = __x->__parent_->__right_;
            } else {
              __w = __x->__parent_->__left_;
            }
          } else {
            if (__tree_is_black(__w->__left_)) {
              __w->__right_->__is_black_ = true;
              __w->__is_black_           = false;
              __tree_left_rotate(__w);
              __w = __w->__parent_;
            }
            __w->__is_black_            = __w->__parent_->__is_black_;
            __w->__parent_->__is_black_ = true;
            __w->__left_->__is_black_   = true;
            __tree_right_rotate(__w->__parent_);
            break;
          }
        }
      }
    }
  }
}

}  // namespace ft

#endif  // INCLUDES_TREE_UTIL_HPP_
