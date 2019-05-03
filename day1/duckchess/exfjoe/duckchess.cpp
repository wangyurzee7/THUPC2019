#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

const int chessR = 10, chessC = 9;
const int Red = 0, Blue = 1;
const char player_name[2][5] = {"red", "blue"};
const char piece_name[7][10] = {"captain", "guard", "elephant", "horse", "car", "duck", "soldier"};
const char invalid[20] = "Invalid command";

struct Piece {
  enum corps {captain, guard, elephant, horse, car, duck, soldier, empty};
  int color;
  corps corp;

  Piece(int color = Red, corps corp = Piece::empty) :
    color(color), corp(corp) {}

  void reset() {
    corp = Piece::empty;
  }

  bool isEmpty() const {
    return corp == Piece::empty;
  }

  bool selected(int player) const {
    return color == player;
  }

  bool moveable(int player) const {
    return corp == Piece::empty || color != player;
  }
};

struct Chess {
  int cur_player;
  bool game_over;
  Piece piece[chessR][chessC];
  bool reachable[chessR][chessC];

  Chess() {
    cur_player = Red;
    game_over = false;
    for (int i = 0; i < chessR; ++i)
      for (int j = 0; j < chessC; ++j)
        piece[i][j] = Piece();
    piece[0][0] = piece[0][8] = Piece(Red, Piece::car);
    piece[0][1] = piece[0][7] = Piece(Red, Piece::horse);
    piece[0][2] = piece[0][6] = Piece(Red, Piece::elephant);
    piece[0][3] = piece[0][5] = Piece(Red, Piece::guard);
    piece[0][4] = Piece(Red, Piece::captain);
    piece[2][0] = piece[2][8] = Piece(Red, Piece::duck);
    piece[3][0] = piece[3][2] = piece[3][4] = piece[3][6] = piece[3][8]
        = Piece(Red, Piece::soldier);

    piece[9][0] = piece[9][8] = Piece(Blue, Piece::car);
    piece[9][1] = piece[9][7] = Piece(Blue, Piece::horse);
    piece[9][2] = piece[9][6] = Piece(Blue, Piece::elephant);
    piece[9][3] = piece[9][5] = Piece(Blue, Piece::guard);
    piece[9][4] = Piece(Blue, Piece::captain);
    piece[7][0] = piece[7][8] = Piece(Blue, Piece::duck);
    piece[6][0] = piece[6][2] = piece[6][4] = piece[6][6] = piece[6][8]
        = Piece(Blue, Piece::soldier);
  }

  bool inside(int x, int y) {
    return x >= 0 && x < chessR && y >= 0 && y < chessC;
  }

  bool isEmpty(int x, int y) const {
    return piece[x][y].isEmpty();
  }

  bool selected(int x, int y) const {
    return piece[x][y].selected(cur_player);
  }

  bool moveable(int x, int y) {
    return inside(x, y) && piece[x][y].moveable(cur_player);
  }

  void getReachable(int x, int y) {
    memset(reachable, false, sizeof(reachable));
    if (piece[x][y].corp == Piece::captain) {
      const int dx[4] = {1, 0, -1, 0};
      const int dy[4] = {0, 1, 0, -1};
      for (int d = 0; d < 4; ++d) {
        int x2 = x + dx[d], y2 = y + dy[d];
        if (moveable(x2, y2))
          reachable[x2][y2] = true;
      }
    } else if (piece[x][y].corp == Piece::guard) {
      const int dx[4] = {1, -1, -1, 1};
      const int dy[4] = {1, 1, -1, -1};
      for (int d = 0; d < 4; ++d) {
        int x2 = x + dx[d], y2 = y + dy[d];
        if (moveable(x2, y2))
          reachable[x2][y2] = true;
      }
    } else if (piece[x][y].corp == Piece::elephant) {
      const int dx[4] = {1, -1, -1, 1};
      const int dy[4] = {1, 1, -1, -1};
      for (int d = 0; d < 4; ++d) {
        int x1 = x + dx[d], y1 = y + dy[d];
        if (inside(x1, y1) && isEmpty(x1, y1)) {
          int x2 = x1 + dx[d], y2 = y1 + dy[d];
          if (moveable(x2, y2))
              reachable[x2][y2] = true;
        }
      }
    } else if (piece[x][y].corp == Piece::horse) {
      const int dx1[8] = {0, 1, 1, 0, 0, -1, -1, 0};
      const int dy1[8] = {-1, 0, 0, 1, 1, 0, 0, -1};
      const int dx2[8] = {1, 2, 2, 1, -1, -2, -2, -1};
      const int dy2[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
      for (int d = 0; d < 8; ++d) {
        int x1 = x + dx1[d], y1 = y + dy1[d];
        if (inside(x1, y1) && isEmpty(x1, y1)) {
          int x2 = x + dx2[d], y2 = y + dy2[d];
          if (moveable(x2, y2))
            reachable[x2][y2] = true;
        }
      }
    } else if (piece[x][y].corp == Piece::car) {
      const int dx[4] = {0, 1, 0, -1};
      const int dy[4] = {-1, 0, 1, 0};
      for (int d = 0; d < 4; ++d) {
        for (int x2 = x + dx[d], y2 = y + dy[d]; moveable(x2, y2); x2 += dx[d], y2 += dy[d]) {
          reachable[x2][y2] = true;
          if (!isEmpty(x2, y2)) break;
        }
      }
    } else if (piece[x][y].corp == Piece::duck) {
      const int dx[4] = {1, 1, -1, -1};
      const int dy[4] = {-1, 1, -1, 1};
      for (int d = 0; d < 4; ++d) {
        int x1 = x + dx[d], y1 = y;
        int x2 = x + dx[d] * 2, y2 = y + dy[d];
        int x3 = x + dx[d] * 3, y3 = y + dy[d] * 2;
        if (moveable(x3, y3) && isEmpty(x1, y1) && isEmpty(x2, y2))
          reachable[x3][y3] = true;
        x1 = x, y1 = y + dy[d];
        x2 = x + dx[d], y2 = y + dy[d] * 2;
        x3 = x + dx[d] * 2, y3 = y + dy[d] * 3;
        if (moveable(x3, y3) && isEmpty(x1, y1) && isEmpty(x2, y2))
          reachable[x3][y3] = true;
      }
    } else if (piece[x][y].corp == Piece::soldier) {
      const int dx[8] = {1, 1, -1, -1, 0, 0, 1, -1};
      const int dy[8] = {-1, 1, -1, 1, 1, -1, 0, 0};
      for (int d = 0; d < 8; ++d) {
        int x2 = x + dx[d], y2 = y + dy[d];
        if (moveable(x2, y2))
          reachable[x2][y2] = true;
      }
    }
  }

  void play(int x1, int y1, int x2, int y2) {
    if (piece[x2][y2].corp == Piece::captain)
      game_over = true;
    piece[x2][y2] = piece[x1][y1];
    piece[x1][y1].reset();
    cur_player ^= 1;
  }

  bool check() {
    int player = cur_player;
    bool res = false;

    int red_x, red_y, blue_x, blue_y;
    for (int x = 0; x < chessR; ++x) {
      for (int y = 0; y < chessC; ++y) {
        if (piece[x][y].color == Red && piece[x][y].corp == Piece::captain)
          red_x = x, red_y = y;
        if (piece[x][y].color == Blue && piece[x][y].corp == Piece::captain)
          blue_x = x, blue_y = y;
      }
    }

    for (int x = 0; x < chessR && !res; ++x) {
      for (int y = 0; y < chessC && !res; ++y) {
        cur_player = piece[x][y].color;
        getReachable(x, y);
        if (reachable[red_x][red_y] || reachable[blue_x][blue_y])
          res = true;
      }
    }
    cur_player = player;
    return res;
  }
} chess;

int Q;

int main() {
  scanf("%d", &Q);
  for (int i = 1; i <= Q; ++i) {
    int x1, x2, y1, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    if (!chess.inside(x1, y1) || !chess.inside(x2, y2))
      printf("Data Error!\n");
    if (chess.game_over || chess.isEmpty(x1, y1) || !chess.selected(x1, y1)) {
      printf("%s\n", invalid);
      continue;
    }
    chess.getReachable(x1, y1);
    if (!chess.reachable[x2][y2]) {
      printf("%s\n", invalid);
    } else {
      Piece p1 = chess.piece[x1][y1], p2 = chess.piece[x2][y2];
      chess.play(x1, y1, x2, y2);
      printf("%s %s;", player_name[p1.color], piece_name[p1.corp]);
      if (p2.isEmpty())
        printf("NA;");
      else
        printf("%s %s;", player_name[p2.color], piece_name[p2.corp]);
      printf(!chess.game_over && chess.check() ? "yes;" : "no;");
      printf(chess.game_over ? "yes\n" : "no\n");      
    }
  }
  return 0;
}