// Builds a graph with errors, displays it and saves it as an image
void setStyleAlt(){
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1111);
  gStyle->SetOptFit(111);
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

void viscosityalt(){
setStyleAlt();    
    // The values and the errors on the X and Y axis
    const int n_points=4;
    double x_vals[n_points]=
            {20.9,69.3,25.4,34.0};
    double y_vals[n_points]=
            {9.25,31.8,10.2,14.6};
    
   double x_errs[n_points]=
            {0.3,0.5,1.2,0.4};
    double y_errs[n_points]=
        {0.4,0.5,0.9,0.4};

    // Instance of the graph
    TGraphErrors * graph =new TGraphErrors(n_points,x_vals,y_vals,x_errs,y_errs);
    graph->SetTitle(" ; velocit#grave{a} corretta - 10^{-3} (m/s); #beta - 10^{-3} (Kg/s^{2})");

    // Cosmetics
    graph->SetMarkerStyle(kOpenCircle);
    graph->SetMarkerColor(kBlue);
    graph->SetLineColor(kBlue);
    graph->GetXaxis()->SetLimits(0,45);//range asse x
    graph->GetYaxis()->SetRangeUser(0,45);//range asse y


    // The canvas on which we'll draw the graph
    TCanvas *mycanvas = new TCanvas();

    // Define a linear function
    TF1 *f = new TF1("Linear law","x*[1]",0.2,1.2); // Linear fit with just one parameter
    // Let's make the function line nicer
    f->SetLineColor(kRed); f->SetLineStyle(2);
    f->SetParName(1,"#eta"); 
    f->FixParameter(0,0.);    
// Fit it to the graph and draw it
    graph->Fit(f);

    // Draw the graph !
    graph->Draw("APE");

    cout << "x and y measurements correlation =" <<graph->GetCorrelationFactor()<<endl;
    cout << "The Chisquare of the fit = "<< graph->Chisquare(f)<<endl;
    cout << "From function  "<<f->GetChisquare()<<endl;
    cout << "From function  "<<f->GetNDF()<<endl;
 
   // Build and Draw a legend
    TLegend *leg=new TLegend(.1,.7,.3,.9);
    leg->SetFillColor(0);
    graph->SetFillColor(0);
    leg->AddEntry(graph,"Punti Sperimentali");
    leg->AddEntry(f,"Fit Lineare");
    leg->Draw("Same");

    mycanvas->Print("viscosity-alt.gif");
}
