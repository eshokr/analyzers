// Original Author:  Eslam Shokr
//         Created:  sun, 23 Dec 2018 22:36:50 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"

//
// class declaration
//

class DemoAnalyzer2 : public edm::EDAnalyzer {
   public:
      explicit DemoAnalyzer2(const edm::ParameterSet&);
      ~DemoAnalyzer2();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
  TH1D* histo;
     TH1D* demohisto;
     TH1D* size;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
DemoAnalyzer2::DemoAnalyzer2(const edm::ParameterSet& iConfig)
{

  edm::Service<TFileService> fs;
   demohisto = fs->make<TH1D>("eta(0.5)" , "eta(0.5)" , 100 , 0 , 1000 );   
    histo = fs->make<TH1D>("eta(0.1)" , "eta(0.1)" , 100 , 0 , 500 );
       size = fs->make<TH1D>("tracksno." , "tracksno." , 100 , 0 , 3000 );


}


DemoAnalyzer2::~DemoAnalyzer2()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
DemoAnalyzer2::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   Handle<reco::TrackCollection> tracks;
   iEvent.getByLabel("generalTracks", tracks); 
   int k=0; int m =0; int j =0; int l =0;
   for (reco::TrackCollection::const_iterator track = tracks->begin() ; track != tracks->end(); track ++ )
   {
       // tracks selection for track
         // 1- high quality
if (track -> quality(reco::Track::qualityByName("highPurity")))
  // 2- |η| < 2.4
   if (abs (track -> eta()) < 2.4 )
         // 3- pt  0.1 GeV/c < pt <5.0 GeV/c. 
if (track -> pt() >0.1 && track -> pt() <5.0 )
         // 4- σ(pT)/pT < 10 %
if (track-> ptError()/track-> pt() < 0.1)   
         // 5- dz/ σ(dz) < 3
        if (track-> dz()/ track-> dzError() < 3.0)   
  // 6- dxy/ σ(dxy) <3
        if (track-> dxy()/ track-> dxyError() < 3.0)  
        
            
            
            
            
            
            
   for (reco::TrackCollection::const_iterator track1 = tracks->begin() ; track1 != tracks->end(); track1 ++ )
   {
      // tracks selection for track1
         // 1- high quality
if (track1 -> quality(reco::Track::qualityByName("highPurity")))
  // 2- |η| < 2.4
   if (abs (track1 -> eta()) < 2.4 )
         // 3- pt  0.1 GeV/c < pt <5.0 GeV/c. 
if (track1 -> pt() >0.1 && track1 -> pt() <5.0 )
         // 4- σ(pT)/pT < 10 %
if (track1-> ptError()/track1-> pt() < 0.1)   
         // 5- dz/ σ(dz) < 3
        if (track1-> dz()/ track1-> dzError() < 3.0)   
  // 6- dxy/ σ(dxy) <3
        if (track1-> dxy()/ track1-> dxyError() < 3.0)   

  
   if (abs(track->eta() - track1->eta()) <= 0.1)
     { k = k+1;}
   if (abs(track->eta() - track1->eta()) <= 0.5)
     { m = m+1;}   
   }
      if(k > j)
               { j =k;}
      if(m > l)
               { l =m;}
     k =0; m =0; }
   size ->Fill(tracks -> size());
   cout <<"the number of tracks in this event = " << tracks ->size()<<endl;
      histo->Fill(j);
   cout <<"the maximum no of tracks with respect to 0.1 window  = "<< j << endl;
      demohisto->Fill(l);
   cout <<"the maximum no of tracks with respect to 0.5 window  = "<< l << endl;

  
  
#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
DemoAnalyzer2::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DemoAnalyzer2::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
void 
DemoAnalyzer2::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
DemoAnalyzer2::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
DemoAnalyzer2::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
DemoAnalyzer2::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
DemoAnalyzer2::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(DemoAnalyzer2);
