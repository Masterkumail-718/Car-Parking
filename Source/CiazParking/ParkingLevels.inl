void AParkingGameMode::CreateLevels(){
 Levels.Empty();
 { FParkingLevel L;
 L.Name=TEXT("Cone basics");L.Hint=TEXT("Follow the cones. Align and stop with all four wheels inside the bay.");
 L.Spawn=FVector(-1700.000f,0.000f,110.000f);L.Target=FVector(1300.000f,0.000f,0.000f);
 L.SpawnYaw=0;L.TargetYaw=0;L.Width=330;L.Length=560;
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Cone");O.P=FVector(-1100.000f,-260.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Cone");O.P=FVector(-1100.000f,260.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Cone");O.P=FVector(-500.000f,-260.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Cone");O.P=FVector(-500.000f,260.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Cone");O.P=FVector(100.000f,-260.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Cone");O.P=FVector(100.000f,260.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Cone");O.P=FVector(700.000f,-260.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Cone");O.P=FVector(700.000f,260.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Cone");O.P=FVector(1300.000f,-260.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Cone");O.P=FVector(1300.000f,260.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(1770.000f,0.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(1690.000f,-150.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(1690.000f,50.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(1690.000f,250.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(0.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(0.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,0.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,0.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("CurbCorner");O.P=FVector(-2450.000f,1550.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(-2250.000f,1600.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car3");O.P=FVector(-2300.000f,1150.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-2500.000f,1850.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-2100.000f,1850.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 Levels.Add(L); }
 { FParkingLevel L;
 L.Name=TEXT("Reverse lane");L.Hint=TEXT("Select Reverse and back between the bollards. Face the arrow.");
 L.Spawn=FVector(1400.000f,0.000f,110.000f);L.Target=FVector(-850.000f,0.000f,0.000f);
 L.SpawnYaw=0;L.TargetYaw=0;L.Width=320;L.Length=560;
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-850.000f,-250.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-850.000f,250.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-250.000f,-250.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-250.000f,250.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(350.000f,-250.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(350.000f,250.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(950.000f,-250.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(950.000f,250.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-1350.000f,0.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(0.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(0.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,0.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,0.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("CurbCorner");O.P=FVector(-2450.000f,1550.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(-2250.000f,1600.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car3");O.P=FVector(-2300.000f,1150.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-2500.000f,1850.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-2100.000f,1850.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 Levels.Add(L); }
 { FParkingLevel L;
 L.Name=TEXT("Right-angle bay");L.Hint=TEXT("Use the open aisle, turn right and park between the cars.");
 L.Spawn=FVector(-1700.000f,-850.000f,110.000f);L.Target=FVector(850.000f,650.000f,0.000f);
 L.SpawnYaw=0;L.TargetYaw=90;L.Width=300;L.Length=560;
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car1");O.P=FVector(1210.000f,650.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car2");O.P=FVector(490.000f,650.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(1000.000f,1090.000f,0.000f);O.Yaw=180.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(800.000f,1090.000f,0.000f);O.Yaw=180.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(600.000f,1090.000f,0.000f);O.Yaw=180.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Cone");O.P=FVector(-1000.000f,-1250.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Cone");O.P=FVector(-400.000f,-1250.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Cone");O.P=FVector(200.000f,-1250.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(1450.000f,-150.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(0.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(0.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,0.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,0.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("CurbCorner");O.P=FVector(-2450.000f,1550.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(-2250.000f,1600.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car3");O.P=FVector(-2300.000f,1150.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-2500.000f,1850.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-2100.000f,1850.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 Levels.Add(L); }
 { FParkingLevel L;
 L.Name=TEXT("Diagonal parking");L.Hint=TEXT("Line up with the angled bay before entering.");
 L.Spawn=FVector(-1700.000f,-900.000f,110.000f);L.Target=FVector(850.000f,400.000f,0.000f);
 L.SpawnYaw=0;L.TargetYaw=45;L.Width=290;L.Length=560;
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car1");O.P=FVector(1093.952f,156.048f,0.000f);O.Yaw=45.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car2");O.P=FVector(606.048f,643.952f,0.000f);O.Yaw=45.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(1260.122f,597.990f,0.000f);O.Yaw=135.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(1118.701f,739.411f,0.000f);O.Yaw=135.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(977.279f,880.833f,0.000f);O.Yaw=135.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Cone");O.P=FVector(-900.000f,-1150.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Cone");O.P=FVector(-400.000f,-1150.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Cone");O.P=FVector(100.000f,-1150.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car3");O.P=FVector(1450.000f,-900.000f,0.000f);O.Yaw=45.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(0.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(0.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,0.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,0.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("CurbCorner");O.P=FVector(-2450.000f,1550.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(-2250.000f,1600.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car3");O.P=FVector(-2300.000f,1150.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-2500.000f,1850.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-2100.000f,1850.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 Levels.Add(L); }
 { FParkingLevel L;
 L.Name=TEXT("Reverse between cars");L.Hint=TEXT("Drive past the bay, then reverse into it using your sensors.");
 L.Spawn=FVector(1100.000f,450.000f,110.000f);L.Target=FVector(-850.000f,450.000f,0.000f);
 L.SpawnYaw=0;L.TargetYaw=0;L.Width=280;L.Length=560;
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car1");O.P=FVector(-850.000f,125.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car2");O.P=FVector(-850.000f,775.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(-1270.000f,300.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(-1270.000f,500.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(-1270.000f,700.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-1200.000f,1100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-600.000f,1100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(0.000f,1100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(0.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(0.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,0.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,0.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("CurbCorner");O.P=FVector(-2450.000f,1550.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(-2250.000f,1600.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car3");O.P=FVector(-2300.000f,1150.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-2500.000f,1850.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-2100.000f,1850.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 Levels.Add(L); }
 { FParkingLevel L;
 L.Name=TEXT("Parallel by the curb");L.Hint=TEXT("Reverse into the space between the cars beside the curb.");
 L.Spawn=FVector(1050.000f,100.000f,110.000f);L.Target=FVector(0.000f,1100.000f,0.000f);
 L.SpawnYaw=0;L.TargetYaw=0;L.Width=280;L.Length=680;
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car1");O.P=FVector(-610.000f,1100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car2");O.P=FVector(610.000f,1100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(-1200.000f,1450.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(-1000.000f,1450.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(-800.000f,1450.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(-600.000f,1450.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(-400.000f,1450.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(-200.000f,1450.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(0.000f,1450.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(200.000f,1450.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(400.000f,1450.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(600.000f,1450.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(800.000f,1450.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(1000.000f,1450.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(1200.000f,1450.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-1500.000f,1400.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(1500.000f,1400.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(0.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(0.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,0.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,0.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("CurbCorner");O.P=FVector(-2450.000f,1550.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(-2250.000f,1600.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car3");O.P=FVector(-2300.000f,1150.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-2500.000f,1850.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-2100.000f,1850.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 Levels.Add(L); }
 { FParkingLevel L;
 L.Name=TEXT("Barrier corridor");L.Hint=TEXT("Keep centred through the concrete barriers, then park.");
 L.Spawn=FVector(-1800.000f,0.000f,110.000f);L.Target=FVector(1500.000f,0.000f,0.000f);
 L.SpawnYaw=0;L.TargetYaw=0;L.Width=270;L.Length=560;
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-1000.000f,-215.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-1000.000f,215.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-820.000f,-215.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-820.000f,215.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-640.000f,-215.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-640.000f,215.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-460.000f,-215.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-460.000f,215.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-280.000f,-215.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-280.000f,215.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-100.000f,-215.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-100.000f,215.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(80.000f,-215.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(80.000f,215.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(260.000f,-215.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(260.000f,215.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(440.000f,-215.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(440.000f,215.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(620.000f,-215.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(620.000f,215.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(1500.000f,-225.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(1500.000f,225.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(1980.000f,0.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(0.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(0.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,0.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,0.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("CurbCorner");O.P=FVector(-2450.000f,1550.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(-2250.000f,1600.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car3");O.P=FVector(-2300.000f,1150.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-2500.000f,1850.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-2100.000f,1850.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 Levels.Add(L); }
 { FParkingLevel L;
 L.Name=TEXT("Offset approach");L.Hint=TEXT("Pass the staggered barriers, turn around in the open area and reverse into the bay.");
 L.Spawn=FVector(-1950.000f,-650.000f,110.000f);L.Target=FVector(1700.000f,-650.000f,0.000f);
 L.SpawnYaw=0;L.TargetYaw=180;L.Width=280;L.Length=560;
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-650.000f,-1050.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-650.000f,-870.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-650.000f,-690.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-650.000f,-510.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(550.000f,250.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(550.000f,430.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(550.000f,610.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(550.000f,790.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car1");O.P=FVector(1700.000f,-310.000f,0.000f);O.Yaw=180.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car2");O.P=FVector(1700.000f,-990.000f,0.000f);O.Yaw=180.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-650.000f,250.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Cone");O.P=FVector(550.000f,-550.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(0.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(0.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,0.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,0.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("CurbCorner");O.P=FVector(-2450.000f,1550.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(-2250.000f,1600.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car3");O.P=FVector(-2300.000f,1150.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-2500.000f,1850.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-2100.000f,1850.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 Levels.Add(L); }
 { FParkingLevel L;
 L.Name=TEXT("Precision reverse");L.Hint=TEXT("Reverse slowly between the parked cars. Make small corrections.");
 L.Spawn=FVector(1000.000f,450.000f,110.000f);L.Target=FVector(-1000.000f,450.000f,0.000f);
 L.SpawnYaw=0;L.TargetYaw=0;L.Width=245;L.Length=540;
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car1");O.P=FVector(-1000.000f,185.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car2");O.P=FVector(-1000.000f,715.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(-1420.000f,300.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(-1420.000f,500.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(-1420.000f,700.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Cone");O.P=FVector(-600.000f,-250.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Cone");O.P=FVector(0.000f,-250.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Cone");O.P=FVector(600.000f,-250.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(0.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(0.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,0.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,0.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("CurbCorner");O.P=FVector(-2450.000f,1550.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(-2250.000f,1600.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car3");O.P=FVector(-2300.000f,1150.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-2500.000f,1850.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-2100.000f,1850.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 Levels.Add(L); }
 { FParkingLevel L;
 L.Name=TEXT("Final assessment");L.Hint=TEXT("Negotiate the barriers, then parallel park between the cars.");
 L.Spawn=FVector(-2050.000f,-950.000f,110.000f);L.Target=FVector(1000.000f,1050.000f,0.000f);
 L.SpawnYaw=0;L.TargetYaw=0;L.Width=260;L.Length=670;
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car1");O.P=FVector(390.000f,1050.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car3");O.P=FVector(1610.000f,1050.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(0.000f,1400.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(200.000f,1400.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(400.000f,1400.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(600.000f,1400.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(800.000f,1400.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(1000.000f,1400.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(1200.000f,1400.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(1400.000f,1400.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(1600.000f,1400.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(1800.000f,1400.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(2000.000f,1400.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(2200.000f,1400.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-950.000f,-1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-950.000f,-820.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-950.000f,-640.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-950.000f,-460.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-150.000f,300.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-150.000f,480.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Barrier");O.P=FVector(-150.000f,660.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Cone");O.P=FVector(0.000f,-850.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Cone");O.P=FVector(750.000f,-550.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Cone");O.P=FVector(2100.000f,650.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(2250.000f,1350.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(0.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2000.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2200.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2400.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2600.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2800.000f,-2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-1000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(0.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(1800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2000.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2200.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2400.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2600.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2800.000f,2100.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,-200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,0.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(-2900.000f,2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,-200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,0.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1200.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1400.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1600.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,1800.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Wall");O.P=FVector(2900.000f,2000.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("CurbCorner");O.P=FVector(-2450.000f,1550.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Curb");O.P=FVector(-2250.000f,1600.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Car3");O.P=FVector(-2300.000f,1150.000f,0.000f);O.Yaw=90.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-2500.000f,1850.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 { FParkingLevel::FObstacle O;O.Asset=TEXT("Bollard");O.P=FVector(-2100.000f,1850.000f,0.000f);O.Yaw=0.000f;L.Obstacles.Add(O); }
 Levels.Add(L); }
 {
  FParkingLevel L;
  L.Name=TEXT("Barrier bend");
  L.Hint=TEXT("Keep clear of the barriers, then line up slowly in the tighter end bay.");
  L.Spawn=FVector(-2140,-1548,110);
  L.Target=FVector(376,2496,0);
  L.Width=270;L.Length=500;
  L.GroundSize=FVector2D(5800,5800);

  auto AddObstacle=[&L](const TCHAR* Asset, double X, double Y, float Yaw=0, FVector2D Footprint={0,0}){
   L.Obstacles.Add({Asset,FVector(X,Y,0),Yaw,Footprint});
  };
  // The reference's up direction is +X and its right direction is +Y.
  const FVector2D BarrierFootprint(400,150);
  for(int X=-2088;X<=-328;X+=440){
   AddObstacle(TEXT("Barrier"),X,-1825,0,BarrierFootprint);
   AddObstacle(TEXT("Barrier"),X,-1269,0,BarrierFootprint);
  }
  const FVector2D OuterBendFootprint(350,150);
  AddObstacle(TEXT("Barrier"),96,-1765,11,OuterBendFootprint);
  AddObstacle(TEXT("Barrier"),491,-1634,27,OuterBendFootprint);
  AddObstacle(TEXT("Barrier"),821,-1389,48,OuterBendFootprint);
  AddObstacle(TEXT("Barrier"),1040,-1051,66,OuterBendFootprint);
  AddObstacle(TEXT("Barrier"),1135,-663,89,OuterBendFootprint);
  AddObstacle(TEXT("Barrier"),1139,-204,90,BarrierFootprint);
  AddObstacle(TEXT("Barrier"),1139,254,90,BarrierFootprint);
  AddObstacle(TEXT("Barrier"),127,-1158,25,BarrierFootprint);
  AddObstacle(TEXT("Barrier"),469,-863,57,BarrierFootprint);
  AddObstacle(TEXT("Barrier"),607,-429,89,BarrierFootprint);
  AddObstacle(TEXT("Barrier"),609,4,90,BarrierFootprint);
  AddObstacle(TEXT("Barrier"),-2470,-1548,90,FVector2D(540,100));
  AddObstacle(TEXT("Car2"),1177,718,-90);
  AddObstacle(TEXT("Car3"),1177,1238,-90);
  AddObstacle(TEXT("Car1"),1181,1768,-90);
  AddObstacle(TEXT("Car3"),1181,2296,-90);
  AddObstacle(TEXT("Car1"),633,512,-90);
  AddObstacle(TEXT("Car2"),637,1032,-90);
  AddObstacle(TEXT("Car3"),643,1540,-90);
  AddObstacle(TEXT("Car2"),643,2052,-90);
  for(int Along=-2700;Along<=2700;Along+=200){
   AddObstacle(TEXT("Wall"),Along,-2800);
   AddObstacle(TEXT("Wall"),Along,2800);
   AddObstacle(TEXT("Wall"),-2800,Along,90);
   AddObstacle(TEXT("Wall"),2800,Along,90);
  }
  Levels.Add(MoveTemp(L));
 }
 {
  FParkingLevel L;
  L.Name=TEXT("Full house");
  L.Hint=TEXT("Use the cross aisles to reach the open bay on the far side of the lot.");
  L.Spawn=FVector(-700,2470,110);
  L.Target=FVector(980,-2420,0);
  L.TargetYaw=180;L.Width=270;L.Length=500;
  L.GroundSize=FVector2D(3900,6000);

  const TCHAR* Cars[]={TEXT("Car1"),TEXT("Car2"),TEXT("Car3")};
  const int RowX[]={980,320,-700,-1360};
  const int FirstY[]={-2700,-960,1910};
  const int BayCounts[]={4,8,4};
  constexpr int BayPitch=280;
  // Zero denotes an empty bay. The two cross aisles separate the three groups.
  const int ParkedCars[4][3][8]={
   {{3,0,2,1},{1,2,3,1,2,3,1,2},{3,2,0,3}},
   {{3,1,2,3},{1,2,3,1,2,3,1,2},{2,1,3,0}},
   {{3,1,2,3},{1,2,3,1,2,3,1,2},{2,1,0,2}},
   {{3,1,2,3},{1,2,3,1,2,3,1,2},{3,2,3,0}}
  };
  for(int Row=0;Row<UE_ARRAY_COUNT(RowX);++Row){
   const int X=RowX[Row];
   for(int Group=0;Group<UE_ARRAY_COUNT(FirstY);++Group){
    const int Y=FirstY[Group], Count=BayCounts[Group];
    for(int Slot=0;Slot<Count;++Slot){
     const int ParkedModel=ParkedCars[Row][Group][Slot];
     if(ParkedModel) L.Obstacles.Add({Cars[ParkedModel-1],FVector(X,Y+Slot*BayPitch,0),180});
    }
    for(int Line=0;Line<=Count;++Line)
     L.Obstacles.Add({TEXT("Marking"),FVector(X,Y+(Line-.5)*BayPitch,.3),0,FVector2D(510,12)});
    const int EndX=X+(Row%2==0?-255:255);
    L.Obstacles.Add({TEXT("Marking"),FVector(EndX,Y+(Count-1)*BayPitch/2,.3),90,FVector2D(Count*BayPitch,12)});
   }
  }
  for(int Y:{1260,1530}) L.Obstacles.Add({TEXT("Cone"),FVector(100,Y,0)});
  for(int X=-1800;X<=1800;X+=200){
   L.Obstacles.Add({TEXT("Wall"),FVector(X,-2900,0)});
   L.Obstacles.Add({TEXT("Wall"),FVector(X,2900,0)});
  }
  for(int Y=-2800;Y<=2800;Y+=200){
   L.Obstacles.Add({TEXT("Wall"),FVector(-1850,Y,0),90});
   L.Obstacles.Add({TEXT("Wall"),FVector(1850,Y,0),90});
  }
  Levels.Add(MoveTemp(L));
 }
}
