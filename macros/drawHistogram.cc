void drawHistogram() {
    TCanvas *c1 = new TCanvas("c1", "North", 800, 600);
    TCanvas *c2 = new TCanvas("c2", "South", 800, 600);

    TH1F *h1 = new TH1F("h1", "SMD/ZDC North", 7, 0, 7);
    TH1F *h2 = new TH1F("h1", "SMD/ZDC South", 7, 0, 7);

    const char *binLabels[7] = {"all(92,890,501 events)", "ZDC Trigger Only", "SMD Multiplicity>1", "ZDC1>100", "ZDC2>15", "veto<150", "2<radius<4"};
    gStyle->SetOptStat(0);
    int binContents[7] = {92890501, 857345, 764611, 476526, 356751, 193268, 108011};
    int binContents_2[7] = {92890501, 857345, 641087, 436646, 356751, 179858, 99662};

    for (int i = 0; i < 7; ++i) {
        h1->GetXaxis()->SetBinLabel(i + 1, binLabels[i]);
        h1->SetBinContent(i + 1, (double) binContents[i]/binContents[0]);
    }
    c1->cd();
    c1->SetLogy(); 
    h1->Draw("HIST");
    for (int i = 0; i < 7; ++i)
    {
        double binCenter = h1->GetXaxis()->GetBinCenter(i + 1);
        double binContent = h1->GetBinContent(i + 1);
        TText *text = new TText(binCenter, binContent, Form("%.2e", binContent));
        text->SetTextAlign(22);
        text->SetTextAngle(0);
        text->SetTextSize(0.03);
        text->Draw();
    }
    c1->SaveAs("histogram_north.png");
    
    for (int i = 0; i < 7; ++i) {
        h2->GetXaxis()->SetBinLabel(i + 1, binLabels[i]);
        h2->SetBinContent(i + 1, (double) binContents_2[i]/binContents_2[0]);
    }
    c2->SetLogy();
    c2->cd(); 
    h2->Draw("HIST");
    for (int i = 0; i < 7; ++i)
    {
        double binCenter = h2->GetXaxis()->GetBinCenter(i + 1);
        double binContent = h2->GetBinContent(i + 1);
        TText *text = new TText(binCenter, binContent, Form("%.2e", binContent));
        text->SetTextAlign(22);
        text->SetTextAngle(0);
        text->SetTextSize(0.03);
        text->Draw();
    }
    c2->SaveAs("histogram_south.png");
}