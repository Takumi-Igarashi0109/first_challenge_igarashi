#include "first_challenge_igarashi/first_challenge_igarashi.hpp"

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  // FirstChallengeクラスをインスタンス化
  // ポインタを使う
  std::shared_ptr<FirstChallenge> fchallenge = std::make_shared<FirstChallenge>();
  
  // 制御周期を定義
  rclcpp::Rate loop_rate(fchallenge->hz_);

  // rclcpp::ok()によりCtrl+C押すまでプロセスを継続する
  while(rclcpp::ok())
  {
      // センサ情報を取得してから制御を開始
      // インスタンス化の際にポインタを指定したため，メンバ関数を指定する際にはアロー演算子（->）を使用
      if(fchallenge->can_move())
      {
          fchallenge->set_cmd_vel();
      }

      // コールバック関数を実行
      // rosのspinOnce
      // 制御周期内で1度だけコールバック関数を実行する
      rclcpp::spin_some(fchallenge);
      // 次の実行時間まで待つ
      loop_rate.sleep();
  }
  rclcpp::shutdown();

  return 0;
}