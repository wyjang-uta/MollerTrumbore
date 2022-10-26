// detailed geometrical information can be found at
// sbndoc-db 21693

void GeoChecker()
{
  gSystem->Load("libGeom");
  TGeoManager* geom = new TGeoManager("geom", "raytrace");
  geom->SetNsegments(10000);

  // origin
  Double_t origin[3] = {0., 0., 0.};
  Double_t dir[3] = {-0.000204618, 0.110519, 0.993907};

  // Element
  TGeoElementTable* table = gGeoManager->GetElementTable();
  TGeoElement* Ar = table->FindElement("Argon");
  // material
  TGeoMaterial* vacuum = new TGeoMaterial("vacuum", 0., 0., 0.);
  TGeoMaterial* lar = new TGeoMaterial("lar", Ar, 1.3954);
  TGeoMedium* air = new TGeoMedium("air", 0, vacuum);
  TGeoMedium* larmed = new TGeoMedium("larmed", 1, lar);

  // active volume shapes (units in cm)
  double activeVolume_x = 148.20;
  double activeVolume_y = 316.82;
  double activeVolume_z = 1789.90;
  const Double_t rot_matrix[9] = { 0.921035925,  0.000000000, -0.389477631,
                                   0.022715103,  0.998297825,  0.053716629,
                                   0.388814672, -0.058321970,  0.919468161};
  TGeoTranslation* trans = new TGeoTranslation(4.503730, 80.159301, 795.112945);
  TGeoRotation* rot = new TGeoRotation();;
  rot->SetMatrix(rot_matrix);

  TGeoVolume* top = geom->MakeBox("world", air, 3000, 3000, 5000);
  geom->SetTopVolume(top);
  TGeoVolume* icarus = geom->MakeBox("icarus", larmed, activeVolume_x,
                                                       activeVolume_y,
                                                       activeVolume_z);
  top->AddNodeOverlap(icarus, 1, new TGeoCombiTrans(*trans, *rot));
  //icarus->AddNode(top, 0, new TGeoCombiTrans(4.503730, 80.159301, 795.112945, &rot));
  //geom->SetTopVisible(0);
  /*
  geom->CloseGeometry();

  TGeoChecker chk(geom);
  Double_t inter[3];
  Int_t nelem;
  Int_t dim = 3;
  Double_t pout[3];
  cout << chk.ShootRay(origin, -0.000204618, 0.110519, 0.993907, inter, nelem, dim, pout) << endl;
  cout << pout[0] << endl;
  cout << pout[1] << endl;
  cout << pout[2] << endl;

  top->SetVisibility(1);
  top->SetTransparency(50);
  */
  top->SetTransparency(90);
  icarus->SetTransparency(90);
  geom->CloseGeometry();
  top->Draw("ogl");

}
