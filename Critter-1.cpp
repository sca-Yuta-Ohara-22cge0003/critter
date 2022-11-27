//クリッターを作成
//  プレイヤーはやめない限り
//    プレイヤーに選択肢のメニューを表示する
//    プレイヤーがクリッターの話を聞きたい場合
//      クリッターと話せる
//    プレイヤーがクリッターに餌をやりたい場合
//      クリッターに餌をやる
//    プレイヤーがクリッターと遊びたい場合
//      クリッターと遊ぶ

#include <iostream>

using namespace std;

//クラス定義 -- クリッターという新しいタイプを定義する
class Critter {
public:
  //コンストラクタープロトタイプ
  Critter(int hunger = 0, int boredom = 0);
  void Talk();
  void Eat(int food = 4, int tire = 1);
  void Play(int fun = 4);
  void sport(int fun = 5, int food = 2, int tire = 1);
  void work(int tire = 2);

private:
  int m_Hunger;
  int m_Boredom; // Boredom : 退屈
  int m_Tired;   // Tired : 疲れ

  int m_LikeBorder = 10;
  int m_LikePoint = 0;
  int m_LikeLevel = 0;

  int GetMood() const;
  void PassTime(int time = 1);
};

//コンストラクター定義
Critter::Critter(int hunger, int boredom)
    : m_Hunger(hunger), m_Boredom(boredom) {}

inline int Critter::GetMood() const { return (m_Hunger + m_Boredom) * m_Tired; }

void Critter::PassTime(int time) {
  m_Hunger += time;
  m_Boredom += time;
  m_LikePoint += time;

  if (m_LikePoint >= m_LikeBorder) {
    m_LikeLevel++;
    m_LikePoint = 0;
    m_LikeBorder += 5;
  }
}

void Critter::Talk() {
  //クリッターだよ！今は
  cout << "I'm a critter and I feel ";

  int mood = GetMood();
  if (mood > (15 + m_LikeLevel)) {
    //不機嫌だ
    cout << "mad.\n\n";
  } else if (mood > (10 + m_LikeLevel)) {
    //イライラしている
    cout << "frustrated.\n\n";
  } else if (mood > (5 + m_LikeLevel)) {
    //大丈夫だ
    cout << "okay.\n\n";
  } else {
    //幸せだ
    cout << "happy.\n";
  }

  cout << "Like level : " << m_LikeLevel << "\n\n";

  PassTime();
}

void Critter::Eat(int food, int tire) {
  cout << "Brruppp.\n\n";
  m_Hunger -= food;
  if (m_Hunger < 0) {
    m_Hunger = 0;
  }

  m_Tired = tire;

  PassTime();
}

void Critter::Play(int fun) {
  cout << "Wheee!\n\n";

  m_Boredom -= fun;
  if (m_Boredom < 0) {
    m_Boredom = 0;
  }

  PassTime();
}

void Critter::sport(int fun, int food, int tire) {
  cout << "Wheeeeeeeeeee!\n\n";

  m_Boredom -= fun;
  if (m_Boredom < 0) {
    m_Boredom = 0;
  }

  m_Hunger += food;

  m_Tired += tire;
  if (m_Tired > 2) {
    m_Boredom = 2;
  }

  PassTime();
}

int main() {
  Critter crit;

  int choice;

  do {
    cout << "What do you want to do with critters?\n";
    cout << "Quit : 0 | Talk : 1 | Eat : 2 | Play : 3 | sport : 4\n";
    cout << "choice : ";
    cin >> choice;

    switch (choice) {
    case 0:
      cout << "Good-bye.\n";
      break;

    case 1:
      crit.Talk();
      break;

    case 2:
      crit.Eat();
      break;

    case 3:
      crit.Play();
      break;

    case 4:
      crit.sport();
      break;

    default:
      cout << "\nsorry, but " << choice << "isn't a valid choice.\n";
    }
  } while (choice != 0);

  return 0;
}

/*
新たに追加した機能
1 : Tired
　　疲れという変数を作り、funとhungerに直接作用するようにしました。
2 : Like
　　好感度をつくり、レベルに応じてクリッターの状態がhappyになりやすくしました。
*/